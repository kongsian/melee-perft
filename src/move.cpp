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
//  move.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "move.h"
#include "attack.h"
#include "board.h"
#include "piece.h"
#include "square.h"

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

const std::string Move::toString(const move_t move)
{
    std::string s;

    //  from square

    const int from = Move::from(move);
    s += Square::toString(from);

    //  to square

    const int to = Move::to(move);
    s += Square::toString(to);

    //  promotion

    if (Move::isPromote(move))
    {
        const int promote = Move::promote(move);
        s += Piece::toLowerChar(promote);
    }

    return s;
}

const std::string Move::toSan(const move_t move, const Board& board)
{
    std::string s;

    const int from     = Move::from(move);
    const int to       = Move::to(move);
    const int piece    = board.getPiece(from);
    const int captured = board.getPiece(to);

    //  castling

    if (Move::isCastle(move))
    {
        return from < to ? "O-O" : "O-O-O";
    }

    //  moving piece

    if (!Piece::isPawn(piece))
    {
        s += Piece::toUpperChar(piece);
    }

    //  ambiguity checking

    bool ambiguous = false;
    bool sameRank  = false;
    bool sameFile  = false;

    const bit_t all = board.getAll();
    bit_t attackers = 
        (Attack::knight(to)     & board.getMyKnights     ()) |
        (Attack::bishop(to,all) & board.getMyBishopQueens()) |
        (Attack::rook  (to,all) & board.getMyRookQueens  ());
    attackers &= board.getMyPieces(piece);
    Bit::clear(attackers,from);

    while (attackers)
    {
        ambiguous = true;
        const int square = Bit::pop(attackers);

        if (Square::rank(square) == Square::rank(from))
        {
            sameRank = true;
        }
        if (Square::file(square) == Square::file(from))
        {
            sameFile = true;
        }
    }

    //  pawn captures is always ambiguous

    if ((Piece::isPawn(piece) && !Piece::isNone(captured))
    ||  Move::isEnpassant(move))
    {
        ambiguous = true;
    }

    //  add rank or file indicator to SAN

    if (sameFile && sameRank)
    {
        s += Square::toString(from);
    }
    else if (!sameFile && sameRank)
    {
        s += Square::toString(from)[0];
    }
    else if (sameFile && !sameRank)
    {
        s += Square::toString(from)[1];
    }
    else if (ambiguous)
    {
        s += Square::toString(from)[0];
    }

    //  capture

    if (!Piece::isNone(captured) || Move::isEnpassant(move))
    {
        s += 'x';
    }

    //  to square

    s += Square::toString(to);

    //  promotion

    if (Move::isPromote(move))
    {
        const int promote = Move::promote(move);
        s += '=';
        s += Piece::toUpperChar(promote);
    }

    return s;
}
