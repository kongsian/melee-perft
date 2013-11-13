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
//  piece.h
//--------------------------------------------------------------------//

#ifndef PIECE_H
#define PIECE_H

//--------------------------------------------------------------------//
//  constants
//--------------------------------------------------------------------//

namespace Piece
{
    constexpr int Pawn   = 0;
    constexpr int Knight = 1;
    constexpr int Bishop = 2;
    constexpr int Rook   = 3;
    constexpr int Queen  = 4;
    constexpr int King   = 5;
    constexpr int None   = 6;
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

namespace Piece
{
    constexpr int  begin      ();
    constexpr int  end        ();
    constexpr int  size       ();
              int  make       (const char c);
              char toChar     (const int piece, const int color);
              char toUpperChar(const int piece);
              char toLowerChar(const int piece);
    constexpr bool isPawn     (const int piece);
    constexpr bool isKnight   (const int piece);
    constexpr bool isBishop   (const int piece);
    constexpr bool isRook     (const int piece);
    constexpr bool isQueen    (const int piece);
    constexpr bool isKing     (const int piece);
    constexpr bool isNone     (const int piece);
    constexpr bool isValid    (const int piece);
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline constexpr int Piece::begin()
{
    return Piece::Pawn;
}

inline constexpr int Piece::end()
{
    return Piece::King + 1;
}

inline constexpr int Piece::size()
{
    return Piece::end() - Piece::begin();
}

inline constexpr bool Piece::isPawn(const int piece)
{
    return piece == Piece::Pawn;
}

inline constexpr bool Piece::isKnight(const int piece)
{
    return piece == Piece::Knight;
}

inline constexpr bool Piece::isBishop(const int piece)
{
    return piece == Piece::Bishop;
}

inline constexpr bool Piece::isRook(const int piece)
{
    return piece == Piece::Rook;
}

inline constexpr bool Piece::isQueen(const int piece)
{
    return piece == Piece::Queen;
}

inline constexpr bool Piece::isKing(const int piece)
{
    return piece == Piece::King;
}

inline constexpr bool Piece::isNone(const int piece)
{
    return piece == Piece::None;
}

inline constexpr bool Piece::isValid(const int piece)
{
    return Piece::begin() <= piece && piece < Piece::end();
}

#endif  //  PIECE_H
