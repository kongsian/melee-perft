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
//  rank.h
//--------------------------------------------------------------------//

#ifndef RANK_H
#define RANK_H

//--------------------------------------------------------------------//
//  constants
//--------------------------------------------------------------------//

namespace Rank
{
    constexpr int Rank1 = 0;
    constexpr int Rank2 = 1;
    constexpr int Rank3 = 2;
    constexpr int Rank4 = 3;
    constexpr int Rank5 = 4;
    constexpr int Rank6 = 5;
    constexpr int Rank7 = 6;
    constexpr int Rank8 = 7;
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

namespace Rank
{
    constexpr int  begin  ();
    constexpr int  end    ();
    constexpr int  size   ();
    constexpr int  make   (const char c);
    constexpr char toChar (const int rank);
    constexpr bool isValid(const int rank);
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline constexpr int Rank::begin()
{
    return Rank::Rank1;
}

inline constexpr int Rank::end()
{
    return Rank::Rank8 + 1;
}

inline constexpr int Rank::size()
{
    return Rank::end() - Rank::begin();
}

inline constexpr int Rank::make(const char c)
{
    return c - '1';
}

inline constexpr char Rank::toChar(const int rank)
{
    return static_cast<char>(rank + '1');
}

inline constexpr bool Rank::isValid(const int rank)
{
    return Rank::begin() <= rank && rank < Rank::end();
}

#endif  //  RANK_H
