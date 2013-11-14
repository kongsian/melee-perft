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
//  board.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "board.h"
#include "castle.h"
#include "color.h"
#include "file.h"
#include "piece.h"
#include "rank.h"
#include "square.h"
#include "zorbrist.h"

#include <cctype>
#include <iostream>
#include <sstream>

//--------------------------------------------------------------------//
//  constants
//--------------------------------------------------------------------//

const std::string Board::StartFen =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -";
const std::string Board::KiwiPete =
    "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -";

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

Board::Board()
{
    clear();
}

Board::Board(const std::string& fen)
{
    clear();
    fromFen(fen);
}

Board::Board(const Board& board)
{
    for (int square = Square::begin(); square < Square::end(); ++square)
    {
        m_piece[square] = board.m_piece[square];
    }

    m_king[Color::White] = board.m_king[Color::White];
    m_king[Color::Black] = board.m_king[Color::Black];
    m_me                 = board.m_me;
    m_op                 = board.m_op;
    m_castle             = board.m_castle;
    m_enpassant          = board.m_enpassant;
    m_key                = board.m_key;

    //  bitboards

    for (int piece = Piece::begin(); piece < Piece::end(); ++piece)
    {
        m_pieces[Color::White][piece] = board.m_pieces[Color::White][piece];
        m_pieces[Color::Black][piece] = board.m_pieces[Color::Black][piece];
    }
    m_occ[Color::White] = board.m_occ[Color::White];
    m_occ[Color::Black] = board.m_occ[Color::Black];
    m_all               = board.m_all;
    m_pieces_me         = m_pieces[m_me];
    m_pieces_op         = m_pieces[m_op];
}

void Board::clear()
{
    for (auto& p : m_piece)
    {
        p = Piece::None;
    }

    m_king[Color::White] = Square::None;
    m_king[Color::Black] = Square::None;
    m_me                 = Color::None;
    m_op                 = Color::None;
    m_castle             = Castle::None;
    m_enpassant          = Square::None;

    //  bitboards

    for (int piece = Piece::begin(); piece < Piece::end(); ++piece)
    {
        m_pieces[Color::White][piece] = 0ULL;
        m_pieces[Color::Black][piece] = 0ULL;
    }

    m_occ[Color::White] = 0ULL;
    m_occ[Color::Black] = 0ULL;
    m_all               = 0ULL;
    m_pieces_me         = nullptr;
    m_pieces_op         = nullptr;
}

void Board::fromFen(const std::string& fen)
{
    //  use an input stringstream for parsing

    std::istringstream is(fen);
    char c;

    //  FEN: piece placement

    int rank = Rank::end()-1;
    int file = File::begin();

    is >> std::skipws >> c >> std::noskipws;
    while (!isspace(c))
    {
        if (c == '/')
        {
            --rank;
            file = File::begin();
        }

        else if ('1' <= c && c <= '8')
        {
            file += c - '0';
        }

        else
        {
            const int piece  = Piece::make(c);
            const int color  = isupper(c) ? Color::White : Color::Black;
            const int square = Square::make(rank,file);
 
            m_piece[square]  = piece;
            if (Piece::isKing(piece))
            {
                m_king[color] = square;
            }

            Bit::set(m_pieces[color][piece],square);
            Bit::set(m_occ[color],square);
            Bit::set(m_all,square);

            m_key ^= Zorbrist::Piece[color][piece][square];

            ++file;
        }

        is >> c;
    }

    //  FEN: active color

    is >> std::skipws >> c;
    m_me        = Color::make(c);
    m_op        = Color::opposite(m_me);
    m_pieces_me = m_pieces[m_me];
    m_pieces_op = m_pieces[m_op];

    if (isWhiteToMove())
    {
        m_key ^= Zorbrist::Side;
    }

    //  FEN: castling availability

    is >> std::skipws >> c >> std::noskipws;
    while (!isspace(c))
    {
        if (c == 'K'
        &&  Bit::test(m_pieces[Color::White][Piece::King],Square::E1) 
        &&  Bit::test(m_pieces[Color::White][Piece::Rook],Square::H1))
        {
            m_castle |= Castle::E1G1;
        }

        if (c == 'Q'
        &&  Bit::test(m_pieces[Color::White][Piece::King],Square::E1) 
        &&  Bit::test(m_pieces[Color::White][Piece::Rook],Square::A1))
        {
            m_castle |= Castle::E1C1;
        }

        if (c == 'k'
        &&  Bit::test(m_pieces[Color::Black][Piece::King],Square::E8) 
        &&  Bit::test(m_pieces[Color::Black][Piece::Rook],Square::H8))
        {
            m_castle |= Castle::E8G8;
        }

        if (c == 'q'
        &&  Bit::test(m_pieces[Color::Black][Piece::King],Square::E8) 
        &&  Bit::test(m_pieces[Color::Black][Piece::Rook],Square::A8))
        {
            m_castle |= Castle::E8C8;
        }

        is >> c;
    }
    m_key ^= Zorbrist::Castle[m_castle];

    //  FEN: enpassant square
    //  Enpassant square is set only if it is a legal move

    std::string s;
    is >> std::skipws >> s;
    const int enpassant = Square::make(s);

    if ((isWhiteToMove() && Square::rank(enpassant) == Rank::Rank6)
    ||  (isBlackToMove() && Square::rank(enpassant) == Rank::Rank3))
    {
        const int pawn = Square::pawn(enpassant);
        const bit_t b  = Bit::make(pawn);
        const bit_t m  = Bit::shiftNegative01(b) | Bit::shiftPositive01(b);

        if ((Piece::isNone(getPiece(enpassant)))    //  ep square empty
        &&  (getOpPawns() & b)                      //  enemy pawn on epsq
        &&  (getMyPawns() & m))                     //  friendly pawn present
        {
            m_enpassant = enpassant;
            m_key ^= Zorbrist::Enpassant[Square::file(enpassant)];
        }
    }
}

const std::string Board::toFen() const
{
    //  use an output stringstream for parsing

    std::ostringstream os;

    //  FEN: piece placement

    for (int rank = Rank::end()-1; rank >= Rank::begin(); --rank)
    {
        int skip = 0;
        for (int file = File::begin(); file < File::end(); ++file)
        {
            const int square = Square::make(rank,file);
            const int piece  = getPiece(square);
            const int color  = getColor(square);

            if (Piece::isNone(piece))
            {
                ++skip;
            }
            else
            {
                if (skip)
                {
                    os << skip;
                }
                skip = 0;
                os << Piece::toChar(piece,color);
            }
        }

        if (skip)
        {
            os << skip;
        }

        if (rank != Rank::begin())
        {
            os << '/';
        }
    }

    //  FEN: active color
    
    os << ' ' << Color::toChar(m_me);

    //  FEN: castling availability 

    os << ' ' << Castle::toString(m_castle);

    //  FEN: enpassant square

    os << ' ' << Square::toString(m_enpassant);

    return os.str();
}

void Board::print() const
{
    std::cout << "\n+---+---+---+---+---+---+---+---+\n";

    for (int rank = Rank::end()-1; rank >= Rank::begin(); --rank)
    {
        for (int file = File::begin(); file < File::end(); ++file)
        {
            const int square = Square::make(rank,file);
            const int piece  = getPiece(square);
            const int color  = getColor(square);

            std::cout << (Color::isBlack(color) ? "|*" : "| ")
                      << Piece::toChar(piece,color)
                      << ' ';
        }

        std::cout << "|\n+---+---+---+---+---+---+---+---+\n";
    }

    std::cout << '\n'
              << toFen()
              << '\n'
              << std::endl;
}

void Board::moveDo(const move_t move, Undo& undo)
{
    const int from     = Move::from(move);
    const int to       = Move::to(move);
    const int piece    = getPiece(from);
    const int captured = getPiece(to);
    const int me       = m_me;
    const int op       = m_op;

    //  save into undo

    undo.captured  = captured;
    undo.castle    = m_castle;
    undo.enpassant = m_enpassant;
    undo.key       = m_key;

    //  update board

    m_piece[from]  = Piece::None;
    m_piece[to]    = piece;

    if (Piece::isKing(piece))
    {
        m_king[me] = to;
    }

    m_me = op;
    m_op = me;

    m_castle    &= Castle::Mask[from] & Castle::Mask[to];
    m_enpassant  = Square::None;

    //  update key

    const auto& zme = Zorbrist::Piece[me];
    const auto& zop = Zorbrist::Piece[op];

    m_key ^= zme[piece][from] ^ zme[piece][to];
    if (m_castle != undo.castle)
    {
        m_key ^= Zorbrist::Castle[m_castle ^ undo.castle];
    }
    m_key ^= Zorbrist::Side;

    if (undo.enpassant != Square::None)
    {
        m_key ^= Zorbrist::Enpassant[Square::file(undo.enpassant)];
    }

    //  update bitboards

    const bit_t bitFrom = Bit::make(from);
    const bit_t bitTo   = Bit::make(to);
    const bit_t bitMask = bitFrom | bitTo;

    m_pieces_me[piece]  ^= bitMask;
    m_occ[me]           ^= bitMask;

    if (Move::isEnpassant(move))
    {
        const int pawnSquare = Square::pawn(to);
        const bit_t bitPawn  = Bit::make(pawnSquare);

        m_piece[pawnSquare]       = Piece::None;
        m_pieces_op[Piece::Pawn] ^= bitPawn;
        m_occ[op]                ^= bitPawn;
        m_key ^= zop[Piece::Pawn][pawnSquare];
    }

    else if (!Piece::isNone(captured))
    {
        m_pieces_op[captured] ^= bitTo;
        m_occ[op]             ^= bitTo;
        m_key ^= zop[captured][to];
    }

    if (Move::isPromote(move))
    {
        const int promote         = Move::promote(move);
        m_piece[to]               = promote;
        m_pieces_me[Piece::Pawn] ^= bitTo;
        m_pieces_me[promote]     ^= bitTo;
        m_key ^= zme[Piece::Pawn][to] ^ zme[promote][to];
    }

    else if (Move::isCastle(move))
    {
        const int rookFrom = to   + (from < to ? 1 : -2);
        const int rookTo   = from + (from < to ? 1 : -1);

        m_piece[rookFrom]  = Piece::None;
        m_piece[rookTo]    = Piece::Rook;

        const bit_t bitRook = Bit::make(rookFrom) | Bit::make(rookTo);
        m_pieces_me[Piece::Rook] ^= bitRook;
        m_occ[me]                ^= bitRook;
        m_key ^= zme[Piece::Rook][rookFrom] ^ zme[Piece::Rook][rookTo];
    }

    else if (Move::isPawn2(move))
    {
        const int enpassant = Square::pawn(to);
        if (m_pieces_op[Piece::Pawn] & Bit::Pawn[me][enpassant])
        {
            m_enpassant = enpassant;
            m_key ^= Zorbrist::Enpassant[Square::file(enpassant)];
        }
    }

    m_pieces_me = m_pieces[op];
    m_pieces_op = m_pieces[me];
    m_all       = m_occ[Color::White] | m_occ[Color::Black];
}

void Board::moveUndo(const move_t move, const Undo& undo)
{
    const int from     = Move::from(move);
    const int to       = Move::to(move);
    const int piece    = getPiece(to);
    const int captured = undo.captured;
    const int me       = m_op;
    const int op       = m_me;

    m_pieces_me = m_pieces[me];
    m_pieces_op = m_pieces[op];

    //  update board

    m_piece[from] = piece;
    m_piece[to]   = captured;

    if (Piece::isKing(piece))
    {
        m_king[me] = from;
    }

    m_me = me;
    m_op = op;

    m_castle    = undo.castle;
    m_enpassant = undo.enpassant;
    m_key       = undo.key;

    //  update bitboards

    const bit_t bitFrom = Bit::make(from);
    const bit_t bitTo   = Bit::make(to);
    const bit_t bitMask = bitFrom | bitTo;

    m_pieces_me[piece]  ^= bitMask;
    m_occ[me]           ^= bitMask;

    if (Move::isEnpassant(move))
    {
        const int pawnSquare = Square::pawn(to);
        const bit_t bitPawn  = Bit::make(pawnSquare);

        m_piece[pawnSquare]       = Piece::Pawn;
        m_pieces_op[Piece::Pawn] ^= bitPawn;
        m_occ[op]                ^= bitPawn;
    }

    else if (!Piece::isNone(captured))
    {
        m_pieces_op[captured] ^= bitTo;
        m_occ[op]             ^= bitTo;
    }

    if (Move::isPromote(move))
    {
        m_piece[from]             = Piece::Pawn;
        m_pieces_me[Piece::Pawn] ^= bitFrom;
        m_pieces_me[piece]       ^= bitFrom;
    }

    else if (Move::isCastle(move))
    {
        const int rookFrom = to   + (from < to ? 1 : -2);
        const int rookTo   = from + (from < to ? 1 : -1);

        m_piece[rookFrom]  = Piece::Rook;
        m_piece[rookTo]    = Piece::None;

        const bit_t bitRook = Bit::make(rookFrom) | Bit::make(rookTo);
        m_pieces_me[Piece::Rook] ^= bitRook;
        m_occ[me]                ^= bitRook;
    }

    m_all = m_occ[Color::White] | m_occ[Color::Black];
}

Key Board::computeKey() const
{
    Key key;

    bit_t b = m_all;
    while (b)
    {
        const int square = Bit::pop(b);
        const int piece  = getPiece(square);
        const int color  = getColor(square);

        key ^= Zorbrist::Piece[color][piece][square];
    }

    key ^= Zorbrist::Castle[m_castle];

    if (m_enpassant != Square::None)
    {
        key ^= Zorbrist::Enpassant[Square::file(m_enpassant)];
    }

    if (isWhiteToMove())
    {
        key ^= Zorbrist::Side;
    }

    return key;
}
