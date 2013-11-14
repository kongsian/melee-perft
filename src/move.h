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
//  move.h
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  0-5:    from square
//  6-11:   to square
//  12-14:  promote piece
//  15:     castling
//  16:     enpassant
//  17:     double pawn push
//  18-23:  rook from square
//  24-29:  rook to square
//--------------------------------------------------------------------//

#ifndef MOVE_H
#define MOVE_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "piece.h"

#include <cstdint>
#include <string>

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

using move_t = int32_t;

//--------------------------------------------------------------------//
//  constants
//--------------------------------------------------------------------//

namespace Move
{
    constexpr move_t PromoteKnight = Piece::Knight << 12;
    constexpr move_t PromoteBishop = Piece::Bishop << 12;
    constexpr move_t PromoteRook   = Piece::Rook   << 12; 
    constexpr move_t PromoteQueen  = Piece::Queen  << 12;

    constexpr move_t Promote       = 7 << 12;
    constexpr move_t Castle        = 1 << 15;
    constexpr move_t Enpassant     = 1 << 16;
    constexpr move_t Pawn2         = 1 << 17;
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

class Board;

namespace Move
{
    constexpr move_t make       (const int from, const int to, const int flag=0);
    constexpr int    from       (const move_t move);
    constexpr int    to         (const move_t move);
    constexpr int    promote    (const move_t move);
    constexpr bool   isPromote  (const move_t move);
    constexpr bool   isCastle   (const move_t move);
    constexpr bool   isEnpassant(const move_t move);
    constexpr bool   isPawn2    (const move_t move);
    const std::string toString  (const move_t move);
    const std::string toSan     (const move_t move, const Board& board);
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline constexpr move_t Move::make(const int from, const int to, const int flag)
{
    return static_cast<move_t>(from | (to << 6) | flag);
}

inline constexpr int Move::from(const move_t move)
{
    return move & 0x3f;
}

inline constexpr int Move::to(const move_t move)
{
    return (move >> 6) & 0x3f;
}

inline constexpr int Move::promote(const move_t move)
{
    return (move >> 12) & 0x07;
}

inline constexpr bool Move::isPromote(const move_t move)
{
    return move & Move::Promote;
}

inline constexpr bool Move::isCastle(const move_t move)
{
    return move & Move::Castle;
}

inline constexpr bool Move::isEnpassant(const move_t move)
{
    return move & Move::Enpassant;
}

inline constexpr bool Move::isPawn2(const move_t move)
{
    return move & Move::Pawn2;
}

#endif  //  MOVE_H
