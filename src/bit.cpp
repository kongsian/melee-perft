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
//  bit.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "bit.h"
#include "cpu.h"
#include "color.h"
#include "file.h"
#include "rank.h"
#include "square.h"

#include <iostream>

//--------------------------------------------------------------------//
//  variables
//--------------------------------------------------------------------//

namespace Bit
{
    bit_t Pawn  [Color ::size()][Square::size()];
    bit_t Knight[Square::size()];
    bit_t Bishop[Square::size()];
    bit_t Rook  [Square::size()];
    bit_t King  [Square::size()];
    bit_t Xray  [Square::size()][Square::size()];
    bit_t Sray  [Square::size()][Square::size()];
    int   (*countFp)(const bit_t);
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

namespace
{
    void initPawn    ();
    void initKnight  ();
    void initBishop  ();
    void initRook    ();
    void initKing    ();
    void initRays    ();
    void initCount   ();
    int  countBuiltin(const bit_t b);
    int  countSwar   (const bit_t b);
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

void Bit::init()
{
    initPawn  ();
    initKnight();
    initBishop();
    initRook  ();
    initKing  ();
    initRays  ();
    initCount ();
}

void Bit::print(const bit_t b)
{
    std::cout << '\n';

    for (int rank = Rank::end()-1; rank >= Rank::begin(); --rank)
    {
        for (int file = File::begin(); file < File::end(); ++file)
        {
            const int square = Square::make(rank,file);
            std::cout << (Bit::test(b,square) ? "x " : ". ");
        }
        std::cout << '\n';
    }

    std::cout << std::endl;
}

//  Kogge-Stone occluded fill routines

bit_t Bit::fillNegative09(bit_t b, bit_t all)
{
    all &= ~Bit::FileH;
    b   |= all & (b   >>  9);
    all &=       (all >>  9);
    b   |= all & (b   >> 18);
    all &=       (all >> 18);
    b   |= all & (b   >> 36);
    return b;
}

bit_t Bit::fillNegative08(bit_t b, bit_t all)
{
    b   |= all & (b   >>  8);
    all &=       (all >>  8);
    b   |= all & (b   >> 16);
    all &=       (all >> 16);
    b   |= all & (b   >> 32);
    return b;
}

bit_t Bit::fillNegative07(bit_t b, bit_t all)
{
    all &= ~Bit::FileA;
    b   |= all & (b   >>  7);
    all &=       (all >>  7);
    b   |= all & (b   >> 14);
    all &=       (all >> 14);
    b   |= all & (b   >> 28);
    return b;
}

bit_t Bit::fillNegative01(bit_t b, bit_t all)
{
    all &= ~Bit::FileH;
    b   |= all & (b   >> 1);
    all &=       (all >> 1);
    b   |= all & (b   >> 2);
    all &=       (all >> 2);
    b   |= all & (b   >> 4);
    return b;
}

bit_t Bit::fillPositive01(bit_t b, bit_t all)
{
    all &= ~Bit::FileA;
    b   |= all & (b   << 1);
    all &=       (all << 1);
    b   |= all & (b   << 2);
    all &=       (all << 2);
    b   |= all & (b   << 4);
    return b;
}

bit_t Bit::fillPositive07(bit_t b, bit_t all)
{
    all &= ~Bit::FileH;
    b   |= all & (b   <<  7);
    all &=       (all <<  7);
    b   |= all & (b   << 14);
    all &=       (all << 14);
    b   |= all & (b   << 28);
    return b;
}

bit_t Bit::fillPositive08(bit_t b, bit_t all)
{
    b   |= all & (b   <<  8);
    all &=       (all <<  8);
    b   |= all & (b   << 16);
    all &=       (all << 16);
    b   |= all & (b   << 32);
    return b;
}

bit_t Bit::fillPositive09(bit_t b, bit_t all)
{
    all &= ~Bit::FileA;
    b   |= all & (b   <<  9);
    all &=       (all <<  9);
    b   |= all & (b   << 18);
    all &=       (all << 18);
    b   |= all & (b   << 36);
    return b;
}

namespace
{
    void initPawn()
    {
        auto& wp = Bit::Pawn[Color::White];
        auto& bp = Bit::Pawn[Color::Black];

        for (int square = Square::begin(); square < Square::end(); ++square)
        {
            const bit_t b = Bit::make(square);
            wp[square] = Bit::shiftPositive07(b) | Bit::shiftPositive09(b);
            bp[square] = Bit::shiftNegative07(b) | Bit::shiftNegative09(b);
        }
    }

    void initKnight()
    {
        for (int square = Square::begin(); square < Square::end(); ++square)
        {
            const bit_t b = Bit::make(square);
            Bit::Knight[square] = Bit::shiftNegative17(b) |
                                  Bit::shiftNegative15(b) |
                                  Bit::shiftNegative10(b) |
                                  Bit::shiftNegative06(b) |
                                  Bit::shiftPositive06(b) |
                                  Bit::shiftPositive10(b) |
                                  Bit::shiftPositive15(b) |
                                  Bit::shiftPositive17(b);
        }
    }

    void initBishop()
    {
        for (int square = Square::begin(); square < Square::end(); ++square)
        {
            const bit_t b = Bit::make(square);
            Bit::Bishop[square] = Bit::fillNegative09(b) |
                                  Bit::fillNegative07(b) |
                                  Bit::fillPositive07(b) |
                                  Bit::fillPositive09(b);
            Bit::Bishop[square] ^= b;
        }
    }

    void initRook()
    {
        for (int square = Square::begin(); square < Square::end(); ++square)
        {
            const bit_t b = Bit::make(square);
            Bit::Rook[square] = Bit::fillNegative08(b) |
                                Bit::fillNegative01(b) |
                                Bit::fillPositive01(b) |
                                Bit::fillPositive08(b);
            Bit::Rook[square] ^= b;
        }
    }

    void initKing()
    {
        for (int square = Square::begin(); square < Square::end(); ++square)
        {
            const bit_t b = Bit::make(square);
            Bit::King[square] = Bit::shiftNegative09(b) |
                                Bit::shiftNegative08(b) |
                                Bit::shiftNegative07(b) |
                                Bit::shiftNegative01(b) |
                                Bit::shiftPositive01(b) |
                                Bit::shiftPositive07(b) |
                                Bit::shiftPositive08(b) |
                                Bit::shiftPositive09(b);
        }
    }

    //  Xray[c3][f6] = d4..h8 diagonal bits are set.
    //  Sray[c3][f6] = d4, e5 bits are set.

    void initRays()
    {
        //  array of function pointers to bitfill routines

        bit_t (*fill[])(const bit_t, const bit_t) =
        {
            Bit::fillNegative09,
            Bit::fillNegative08,
            Bit::fillNegative07,
            Bit::fillNegative01,
            Bit::fillPositive01,
            Bit::fillPositive07,
            Bit::fillPositive08,
            Bit::fillPositive09,
        };

        for (int from = Square::begin(); from < Square::end(); ++from)
        {
            auto& xray = Bit::Xray[from];
            auto& sray = Bit::Sray[from];

            for (int to = Square::begin(); to < Square::end(); ++to)
            {
                xray[to] = 0ULL;
                sray[to] = 0ULL;
            }

            const bit_t b = Bit::make(from);

            for (const auto f : fill)
            {
                bit_t c = f(b,~0ULL) ^ b;
                const bit_t d = c;
                while (c)
                {
                    const int to = Bit::pop(c);
                    xray[to] = d;
                    sray[to] = d ^ f(Bit::make(to),~0ULL);
                }
            }
        }
    }

    //  Bit counting will use the hardware popcnt instruction if available.
    //  Otherwise it will fall back to the slow popcount algorithm.

    void initCount()
    {
        Cpu cpu;
        Bit::countFp = cpu.hasPopcnt() ? countBuiltin : countSwar;
    }

    int countBuiltin(const bit_t b)
    {
        return __builtin_popcountll(b);
    }

    int countSwar(bit_t b)
    {
        constexpr bit_t K1 = 0x5555555555555555ULL;
        constexpr bit_t K2 = 0x3333333333333333ULL;
        constexpr bit_t K4 = 0x0f0f0f0f0f0f0f0fULL;
        constexpr bit_t Kf = 0x0101010101010101ULL;

        b =  b       - ((b >> 1)  & K1);
        b = (b & K2) + ((b >> 2)  & K2);
        b = (b       +  (b >> 4)) & K4 ;
        b = (b * Kf) >> 56;
        return static_cast<int>(b);
    }
}
