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
//  bit.h
//--------------------------------------------------------------------//

#ifndef BIT_H
#define BIT_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "square.h"

#include <cstdint>

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

using bit_t = uint64_t;

//--------------------------------------------------------------------//
//  constants
//--------------------------------------------------------------------//

namespace Bit
{
    constexpr bit_t FileA = 0x0101010101010101ULL;
    constexpr bit_t FileB = 0x0202020202020202ULL;
    constexpr bit_t FileC = 0x0404040404040404ULL;
    constexpr bit_t FileD = 0x0808080808080808ULL;
    constexpr bit_t FileE = 0x1010101010101010ULL;
    constexpr bit_t FileF = 0x2020202020202020ULL;
    constexpr bit_t FileG = 0x4040404040404040ULL;
    constexpr bit_t FileH = 0x8080808080808080ULL;

    constexpr bit_t Rank1 = 0x00000000000000ffULL;
    constexpr bit_t Rank2 = 0x000000000000ff00ULL;
    constexpr bit_t Rank3 = 0x0000000000ff0000ULL;
    constexpr bit_t Rank4 = 0x00000000ff000000ULL;
    constexpr bit_t Rank5 = 0x000000ff00000000ULL;
    constexpr bit_t Rank6 = 0x0000ff0000000000ULL;
    constexpr bit_t Rank7 = 0x00ff000000000000ULL;
    constexpr bit_t Rank8 = 0xff00000000000000ULL;

    constexpr bit_t F1G1   = 0x0000000000000060ULL;
    constexpr bit_t E1F1G1 = 0x0000000000000070ULL;
    constexpr bit_t B1C1D1 = 0x000000000000000eULL;
    constexpr bit_t C1D1E1 = 0x000000000000001cULL;
    constexpr bit_t F8G8   = 0x6000000000000000ULL;
    constexpr bit_t E8F8G8 = 0x7000000000000000ULL;
    constexpr bit_t B8C8D8 = 0x0e00000000000000ULL;
    constexpr bit_t C8D8E8 = 0x1c00000000000000ULL;
}

//--------------------------------------------------------------------//
//  variables
//--------------------------------------------------------------------//

namespace Bit
{
    extern bit_t Pawn  [][Square::size()];
    extern bit_t Knight[];
    extern bit_t Bishop[];
    extern bit_t Rook  [];
    extern bit_t King  [];
    extern bit_t Xray  [][Square::size()];
    extern bit_t Sray  [][Square::size()];
    extern int   (*countFp)(const bit_t);
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

namespace Bit
{
              void  init ();
              void  print(const bit_t b);
    constexpr bit_t make (const int square);
    constexpr bool  test (const bit_t b, const int square);
    constexpr int   first(const bit_t b);
              int   count(const bit_t b);
              int   pop  (bit_t& b);
              void  set  (bit_t& b, const int square);
              void  clear(bit_t& b, const int square);

    constexpr bit_t shiftNegative09(const bit_t b);
    constexpr bit_t shiftNegative08(const bit_t b);
    constexpr bit_t shiftNegative07(const bit_t b);
    constexpr bit_t shiftNegative01(const bit_t b);
    constexpr bit_t shiftPositive01(const bit_t b);
    constexpr bit_t shiftPositive07(const bit_t b);
    constexpr bit_t shiftPositive08(const bit_t b);
    constexpr bit_t shiftPositive09(const bit_t b);

    constexpr bit_t shiftNegative17(const bit_t b);
    constexpr bit_t shiftNegative15(const bit_t b);
    constexpr bit_t shiftNegative10(const bit_t b);
    constexpr bit_t shiftNegative06(const bit_t b);
    constexpr bit_t shiftPositive06(const bit_t b);
    constexpr bit_t shiftPositive10(const bit_t b);
    constexpr bit_t shiftPositive15(const bit_t b);
    constexpr bit_t shiftPositive17(const bit_t b);

              bit_t fillNegative09 (const bit_t b, const bit_t all=~0ULL);
              bit_t fillNegative08 (const bit_t b, const bit_t all=~0ULL);
              bit_t fillNegative07 (const bit_t b, const bit_t all=~0ULL);
              bit_t fillNegative01 (const bit_t b, const bit_t all=~0ULL);
              bit_t fillPositive01 (const bit_t b, const bit_t all=~0ULL);
              bit_t fillPositive07 (const bit_t b, const bit_t all=~0ULL);
              bit_t fillPositive08 (const bit_t b, const bit_t all=~0ULL);
              bit_t fillPositive09 (const bit_t b, const bit_t all=~0ULL);
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline constexpr bit_t Bit::make(const int square)
{
    return 1ULL << square;
}

inline constexpr bool Bit::test(const bit_t b, const int square)
{
    return b & Bit::make(square);
}

inline constexpr int Bit::first(const bit_t b)
{
    return __builtin_ctzll(b);
}

inline int Bit::count(const bit_t b)
{
    return Bit::countFp(b);
}

inline int Bit::pop(bit_t& b)
{
    const int square = Bit::first(b);
    b ^= Bit::make(square);
    return square;
}

inline void Bit::set(bit_t& b, const int square)
{
    b |= Bit::make(square);
}

inline void Bit::clear(bit_t& b, const int square)
{
    b &= ~Bit::make(square);
}

inline constexpr bit_t Bit::shiftNegative09(const bit_t b)
{
    return (b & ~Bit::FileA) >> 9;
}

inline constexpr bit_t Bit::shiftNegative08(const bit_t b)
{
    return b >> 8;
}

inline constexpr bit_t Bit::shiftNegative07(const bit_t b)
{
    return (b & ~Bit::FileH) >> 7;
}

inline constexpr bit_t Bit::shiftNegative01(const bit_t b)
{
    return (b & ~Bit::FileA) >> 1;
}

inline constexpr bit_t Bit::shiftPositive01(const bit_t b)
{
    return (b & ~Bit::FileH) << 1;
}

inline constexpr bit_t Bit::shiftPositive07(const bit_t b)
{
    return (b & ~Bit::FileA) << 7;
}

inline constexpr bit_t Bit::shiftPositive08(const bit_t b)
{
    return b << 8;
}

inline constexpr bit_t Bit::shiftPositive09(const bit_t b)
{
    return (b & ~Bit::FileH) << 9;
}

inline constexpr bit_t Bit::shiftNegative17(const bit_t b)
{
    return (b & ~Bit::FileA) >> 17;
}

inline constexpr bit_t Bit::shiftNegative15(const bit_t b)
{
    return (b & ~Bit::FileH) >> 15;
}

inline constexpr bit_t Bit::shiftNegative10(const bit_t b)
{
    return (b & ~(Bit::FileA | Bit::FileB)) >> 10;
}

inline constexpr bit_t Bit::shiftNegative06(const bit_t b)
{
    return (b & ~(Bit::FileG | Bit::FileH)) >> 6;
}

inline constexpr bit_t Bit::shiftPositive06(const bit_t b)
{
    return (b & ~(Bit::FileA | Bit::FileB)) << 6;
}

inline constexpr bit_t Bit::shiftPositive10(const bit_t b)
{
    return (b & ~(Bit::FileG | Bit::FileH)) << 10;
}

inline constexpr bit_t Bit::shiftPositive15(const bit_t b)
{
    return (b & ~Bit::FileA) << 15;
}

inline constexpr bit_t Bit::shiftPositive17(const bit_t b)
{
    return (b & ~Bit::FileH) << 17;
}

#endif  //  BIT_H
