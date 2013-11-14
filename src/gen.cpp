//--------------------------------------------------------------------//
//
//  Melee Perft
//  Copyright (C) 2013 Chua Kong Sian.
//
//  This file is part of Melee Perft.
//
//  Melee Perft is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Melee Perft is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with Melee Perft.  If not, see <http://www.gnu.org/licenses/>.
//
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  gen.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "gen.h"
#include "attack.h"
#include "board.h"
#include "move.h"
#include "square.h"

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

Gen::Gen(const Attack& attack, const Board& board) :
    m_attack(attack),
    m_board (board),
    m_king  (board.getMyKing()),
    m_all   (board.getAll()),
    m_target(0ULL)
{
    m_attack.isAttack(m_king) ? evasion() : legal();
}

void Gen::legal()
{
    m_target = m_board.getOpOcc();
    pawnCapture();
    enpassant  ();

    m_target = ~m_all;
    pawnAdvance();

    m_target = ~m_board.getMyOcc();
    knight();
    bishop();
    rook  ();
    queen ();
    king  ();
    castle();
}

void Gen::evasion()
{
    m_target = ~m_board.getMyOcc();
    king();

    //  pieces giving check

    const int me   = m_board.getMe();
    bit_t checkers =
        (m_attack.pawn  (m_king,me)    & m_board.getOpPawns       ()) |
        (m_attack.knight(m_king)       & m_board.getOpKnights     ()) |
        (m_attack.bishop(m_king,m_all) & m_board.getOpBishopQueens()) |
        (m_attack.rook  (m_king,m_all) & m_board.getOpRookQueens  ());

    //  quit if double check

    const bit_t checker = checkers & -checkers;
    checkers ^= checker;
    if (checkers)
    {
        return;
    }

    //  capture checking piece with pawn

    m_target = checker;
    pawnCapture();

    const int square = Bit::first(checker);
    if (square == Square::pawn(m_board.getEnpassant()))
    {
        enpassant();
    }

    //  block with pawns

    m_target = Bit::Sray[m_king][square];
    pawnAdvance();

    //  capture or block with piece

    m_target ^= checker;
    knight();
    bishop();
    rook  ();
    queen ();
}

void Gen::pawnAdvance()
{
    m_board.isWhiteToMove() ? pawnAdvanceWhite() : pawnAdvanceBlack();
}

void Gen::pawnAdvanceWhite()
{
    const bit_t b = m_board.getMyPawns();

    bit_t moves = Bit::shiftPositive08(b) & m_target;
    addPawnMoves(moves,+8);

    moves = Bit::shiftPositive08(b) & Bit::Rank3 & ~m_all;
    moves = Bit::shiftPositive08(moves) & m_target;
    addPawnMoves(moves,+16,Move::Pawn2);
}

void Gen::pawnAdvanceBlack()
{
    const bit_t b = m_board.getMyPawns();

    bit_t moves = Bit::shiftNegative08(b) & m_target;
    addPawnMoves(moves,-8);

    moves = Bit::shiftNegative08(b) & Bit::Rank6 & ~m_all;
    moves = Bit::shiftNegative08(moves) & m_target;
    addPawnMoves(moves,-16,Move::Pawn2);
}

void Gen::pawnCapture()
{
    m_board.isWhiteToMove() ? pawnCaptureWhite() : pawnCaptureBlack();
}

void Gen::pawnCaptureWhite()
{
    const bit_t b = m_board.getMyPawns();

    bit_t moves = Bit::shiftPositive07(b) & m_target;
    addPawnMoves(moves,+7);

    moves = Bit::shiftPositive09(b) & m_target;
    addPawnMoves(moves,+9);
}

void Gen::pawnCaptureBlack()
{
    const bit_t b = m_board.getMyPawns();

    bit_t moves = Bit::shiftNegative07(b) & m_target;
    addPawnMoves(moves,-7);

    moves = Bit::shiftNegative09(b) & m_target;
    addPawnMoves(moves,-9);
}

void Gen::enpassant()
{
    const int epSquare = m_board.getEnpassant();

    if (epSquare != Square::None)
    {
        const int pawnSquare = Square::pawn(epSquare);
        const int op         = m_board.getOp();

        bit_t b = m_board.getMyPawns() & m_attack.pawn(epSquare,op);
        while (b)
        {
            const int from  = Bit::pop(b);
            const bit_t all = m_all ^ Bit::make(from) ^
                              Bit::make(pawnSquare)  ^
                              Bit::make(epSquare);

            if (!(m_attack.bishop(m_king,all) & m_board.getOpBishopQueens())
            &&  !(m_attack.rook  (m_king,all) & m_board.getOpRookQueens  ()))
            {
                m_movelist.addMove(from,epSquare,Move::Enpassant);
            }
        }
    }
}

void Gen::addPawnMoves(bit_t moves, const int delta, const int flag)
{
    while (moves)
    {
        const int to   = Bit::pop(moves);
        const int from = to - delta;

        //  pinned pawn not moving along pinned direction

        if (m_attack.isPinned(from)
        &&  !Bit::test(Bit::Xray[m_king][from],to))
        {
            continue;
        }

        //  promotion

        else if (Bit::test((Bit::Rank1 | Bit::Rank8),to))
        {
            m_movelist.addMove(from,to,Move::PromoteKnight);
            m_movelist.addMove(from,to,Move::PromoteBishop);
            m_movelist.addMove(from,to,Move::PromoteRook  );
            m_movelist.addMove(from,to,Move::PromoteQueen );
        }

        else
        {
            m_movelist.addMove(from,to,flag);
        }
    }
}

void Gen::knight()
{
    bit_t b = m_board.getMyKnights() & ~m_attack.getPinned();
    while (b)
    {
        const int from = Bit::pop(b);
        bit_t moves    = m_attack.knight(from) & m_target;
        addPieceMoves(from,moves);
    }
}

void Gen::bishop()
{
    bit_t b = m_board.getMyBishops();
    while (b)
    {
        const int from = Bit::pop(b);
        bit_t moves    = m_attack.bishop(from,m_all) & m_target;
        if (m_attack.isPinned(from))
        {
            moves &= Bit::Xray[m_king][from];
        }
        addPieceMoves(from,moves);
    }
}

void Gen::rook()
{
    bit_t b = m_board.getMyRooks();
    while (b)
    {
        const int from = Bit::pop(b);
        bit_t moves    = m_attack.rook(from,m_all) & m_target;
        if (m_attack.isPinned(from))
        {
            moves &= Bit::Xray[m_king][from];
        }
        addPieceMoves(from,moves);
    }
}

void Gen::queen()
{
    bit_t b = m_board.getMyQueens();
    while (b)
    {
        const int from = Bit::pop(b);
        bit_t moves    = m_attack.queen(from,m_all) & m_target;
        if (m_attack.isPinned(from))
        {
            moves &= Bit::Xray[m_king][from];
        }
        addPieceMoves(from,moves);
    }
}

void Gen::king()
{
    bit_t moves = m_attack.king(m_king) & m_target & ~m_attack.getAttack();
    addPieceMoves(m_king,moves);
}

void Gen::castle()
{
    m_board.isWhiteToMove() ? castleWhite() : castleBlack();
}

void Gen::castleWhite()
{
    if (  m_board.canCastleE1G1() 
    &&  !(m_all & Bit::F1G1) 
    &&  !(m_attack.getAttack() & Bit::E1F1G1))
    {
        m_movelist.addMove(Square::E1,Square::G1,Move::Castle);
    }

    if (  m_board.canCastleE1C1()
    &&  !(m_all & Bit::B1C1D1)
    &&  !(m_attack.getAttack() & Bit::C1D1E1))
    {
        m_movelist.addMove(Square::E1,Square::C1,Move::Castle);
    }
}

void Gen::castleBlack()
{
    if (  m_board.canCastleE8G8() 
    &&  !(m_all & Bit::F8G8) 
    &&  !(m_attack.getAttack() & Bit::E8F8G8))
    {
        m_movelist.addMove(Square::E8,Square::G8,Move::Castle);
    }

    if (  m_board.canCastleE8C8()
    &&  !(m_all & Bit::B8C8D8)
    &&  !(m_attack.getAttack() & Bit::C8D8E8))
    {
        m_movelist.addMove(Square::E8,Square::C8,Move::Castle);
    }
}
