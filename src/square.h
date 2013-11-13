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
//  square.h
//--------------------------------------------------------------------//

#ifndef SQUARE_H
#define SQUARE_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include <string>

//--------------------------------------------------------------------//
//  constants
//--------------------------------------------------------------------//

namespace Square
{
    constexpr int A1   =  0;
    constexpr int B1   =  1;
    constexpr int C1   =  2;
    constexpr int D1   =  3;
    constexpr int E1   =  4;
    constexpr int F1   =  5;
    constexpr int G1   =  6;
    constexpr int H1   =  7;
    constexpr int A2   =  8;
    constexpr int B2   =  9;
    constexpr int C2   = 10;
    constexpr int D2   = 11;
    constexpr int E2   = 12;
    constexpr int F2   = 13;
    constexpr int G2   = 14;
    constexpr int H2   = 15;
    constexpr int A3   = 16;
    constexpr int B3   = 17;
    constexpr int C3   = 18;
    constexpr int D3   = 19;
    constexpr int E3   = 20;
    constexpr int F3   = 21;
    constexpr int G3   = 22;
    constexpr int H3   = 23;
    constexpr int A4   = 24;
    constexpr int B4   = 25;
    constexpr int C4   = 26;
    constexpr int D4   = 27;
    constexpr int E4   = 28;
    constexpr int F4   = 29;
    constexpr int G4   = 30;
    constexpr int H4   = 31;
    constexpr int A5   = 32;
    constexpr int B5   = 33;
    constexpr int C5   = 34;
    constexpr int D5   = 35;
    constexpr int E5   = 36;
    constexpr int F5   = 37;
    constexpr int G5   = 38;
    constexpr int H5   = 39;
    constexpr int A6   = 40;
    constexpr int B6   = 41;
    constexpr int C6   = 42;
    constexpr int D6   = 43;
    constexpr int E6   = 44;
    constexpr int F6   = 45;
    constexpr int G6   = 46;
    constexpr int H6   = 47;
    constexpr int A7   = 48;
    constexpr int B7   = 49;
    constexpr int C7   = 50;
    constexpr int D7   = 51;
    constexpr int E7   = 52;
    constexpr int F7   = 53;
    constexpr int G7   = 54;
    constexpr int H7   = 55;
    constexpr int A8   = 56;
    constexpr int B8   = 57;
    constexpr int C8   = 58;
    constexpr int D8   = 59;
    constexpr int E8   = 60;
    constexpr int F8   = 61;
    constexpr int G8   = 62;
    constexpr int H8   = 63;
    constexpr int None = 64;
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

namespace Square
{
    constexpr int         begin   ();
    constexpr int         end     ();
    constexpr int         size    ();
    constexpr int         make    (const int rank, const int file);
              int         make    (const std::string& s);
    constexpr int         rank    (const int square);
    constexpr int         file    (const int square);
    constexpr int         pawn    (const int square);
    constexpr bool        isValid (const int square);
    const     std::string toString(const int square);
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline constexpr int Square::begin()
{
    return Square::A1;
}

inline constexpr int Square::end()
{
    return Square::H8 + 1;
}

inline constexpr int Square::size()
{
    return Square::end() - Square::begin();
}

inline constexpr int Square::make(const int rank, const int file)
{
    return (rank << 3) | file;
}

inline constexpr int Square::rank(const int square)
{
    return square >> 3;
}

inline constexpr int Square::file(const int square)
{
    return square & 7;
}

//  This function computes the square of the enemy pawn given the
//  enpassant square and vice versa.

inline constexpr int Square::pawn(const int square)
{
    return square ^ 8;
}

inline constexpr bool Square::isValid(const int square)
{
    return Square::begin() <= square && square < Square::end();
}

#endif  //  SQUARE_H
