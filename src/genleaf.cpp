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
//  genleaf.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "genleaf.h"
#include "attack.h"
#include "board.h"

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

Genleaf::Genleaf(const Attack& attack, const Board& board) :
    m_attack(attack),
    m_board (board),
    m_size  (0),
    m_king  (board.getMyKing()),
    m_all   (board.getAll()),
    m_target(0ULL)
{
    m_attack.isAttack(m_king) ? evasion() : legal();
}

void Genleaf::legal()
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

void Genleaf::evasion()
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

void Genleaf::pawnAdvance()
{
    m_board.isWhiteToMove() ? pawnAdvanceWhite() : pawnAdvanceBlack();
}

void Genleaf::pawnAdvanceWhite()
{
    //  exclude pins and promotions
 
    bit_t b = m_board.getMyPawns();
    bit_t c = b & ~(m_attack.getPinned() | Bit::Rank7);

    bit_t moves = Bit::shiftPositive08(c) & m_target;
    m_size += Bit::count(moves);

    moves = Bit::shiftPositive08(c) & Bit::Rank3 & ~m_all;
    moves = Bit::shiftPositive08(moves) & m_target;
    m_size += Bit::count(moves);

    //  pins and promotions
 
    b ^= c;
    if (b)
    {
        moves = Bit::shiftPositive08(b) & m_target;
        addPawnMoves(moves,+8);

        moves = Bit::shiftPositive08(b) & Bit::Rank3 & ~m_all;
        moves = Bit::shiftPositive08(moves) & m_target;
        addPawnMoves(moves,+16);
    }
}

void Genleaf::pawnAdvanceBlack()
{
    //  exclude pins and promotions
 
    bit_t b = m_board.getMyPawns();
    bit_t c = b & ~(m_attack.getPinned() | Bit::Rank2);

    bit_t moves = Bit::shiftNegative08(c) & m_target;
    m_size += Bit::count(moves);

    moves = Bit::shiftNegative08(c) & Bit::Rank6 & ~m_all;
    moves = Bit::shiftNegative08(moves) & m_target;
    m_size += Bit::count(moves);

    //  pins and promotions

    b ^= c;
    if (b)
    {
        moves = Bit::shiftNegative08(b) & m_target;
        addPawnMoves(moves,-8);

        moves = Bit::shiftNegative08(b) & Bit::Rank6 & ~m_all;
        moves = Bit::shiftNegative08(moves) & m_target;
        addPawnMoves(moves,-16);
    }
}

void Genleaf::pawnCapture()
{
    m_board.isWhiteToMove() ? pawnCaptureWhite() : pawnCaptureBlack();
}

void Genleaf::pawnCaptureWhite()
{
    //  exclude pins and promotions
 
    bit_t b = m_board.getMyPawns();
    bit_t c = b & ~(m_attack.getPinned() | Bit::Rank7);

    bit_t moves = Bit::shiftPositive07(c) & m_target;
    m_size += Bit::count(moves);

    moves = Bit::shiftPositive09(c) & m_target;
    m_size += Bit::count(moves);

    //  pins and promotions

    b ^= c;
    if (b)
    {
        moves = Bit::shiftPositive07(b) & m_target;
        addPawnMoves(moves,+7);

        moves = Bit::shiftPositive09(b) & m_target;
        addPawnMoves(moves,+9);
    }
}

void Genleaf::pawnCaptureBlack()
{
    //  exclude pins and promotions

    bit_t b = m_board.getMyPawns();
    bit_t c = b & ~(m_attack.getPinned() | Bit::Rank2);

    bit_t moves = Bit::shiftNegative07(c) & m_target;
    m_size += Bit::count(moves);

    moves = Bit::shiftNegative09(c) & m_target;
    m_size += Bit::count(moves);

    //  pins and promotions

    b ^= c;
    if (b)
    {
        moves = Bit::shiftNegative07(b) & m_target;
        addPawnMoves(moves,-7);

        moves = Bit::shiftNegative09(b) & m_target;
        addPawnMoves(moves,-9);
    }
}

void Genleaf::enpassant()
{
    const int ep_square = m_board.getEnpassant();

    if (ep_square != Square::None)
    {
        const int pawn_square = Square::pawn(ep_square);
        const int op          = m_board.getOp();

        bit_t b = m_board.getMyPawns() & m_attack.pawn(ep_square,op);
        while (b)
        {
            const int from  = Bit::pop(b);
            const bit_t all = m_all ^ Bit::make(from) ^
                              Bit::make(pawn_square)  ^
                              Bit::make(ep_square);

            if (!(m_attack.bishop(m_king,all) & m_board.getOpBishopQueens())
            &&  !(m_attack.rook  (m_king,all) & m_board.getOpRookQueens  ()))
            {
                ++m_size;
            }
        }
    }
}

void Genleaf::addPawnMoves(bit_t moves, const int delta)
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
            m_size += 4;
        }

        else
        {
            ++m_size;
        }
    }
}

void Genleaf::knight()
{
    bit_t b = m_board.getMyKnights() & ~m_attack.getPinned();
    while (b)
    {
        const int from = Bit::pop(b);
        bit_t moves    = m_attack.knight(from) & m_target;
        m_size += Bit::count(moves);
    }
}

void Genleaf::bishop()
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
        m_size += Bit::count(moves);
    }
}

void Genleaf::rook()
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
        m_size += Bit::count(moves);
    }
}

void Genleaf::queen()
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
        m_size += Bit::count(moves);
    }
}

void Genleaf::king()
{
    bit_t moves = m_attack.king(m_king) & m_target & ~m_attack.getAttack();
    m_size += Bit::count(moves);
}

void Genleaf::castle()
{
    m_board.isWhiteToMove() ? castleWhite() : castleBlack();
}

void Genleaf::castleWhite()
{
    if (  m_board.canCastleE1G1() 
    &&  !(m_all & Bit::F1G1) 
    &&  !(m_attack.getAttack() & Bit::E1F1G1))
    {
        ++m_size;
    }

    if (  m_board.canCastleE1C1()
    &&  !(m_all & Bit::B1C1D1)
    &&  !(m_attack.getAttack() & Bit::C1D1E1))
    {
        ++m_size;
    }
}

void Genleaf::castleBlack()
{
    if (  m_board.canCastleE8G8() 
    &&  !(m_all & Bit::F8G8) 
    &&  !(m_attack.getAttack() & Bit::E8F8G8))
    {
        ++m_size;
    }

    if (  m_board.canCastleE8C8()
    &&  !(m_all & Bit::B8C8D8)
    &&  !(m_attack.getAttack() & Bit::C8D8E8))
    {
        ++m_size;
    }
}
