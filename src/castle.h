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
//  castle.h
//--------------------------------------------------------------------//

#ifndef CASTLE_H
#define CASTLE_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include <string>

//--------------------------------------------------------------------//
//  constants
//--------------------------------------------------------------------//

namespace Castle
{
    constexpr int None = 0;
    constexpr int E1G1 = 1;
    constexpr int E1C1 = 2;
    constexpr int E8G8 = 4;
    constexpr int E8C8 = 8;
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

namespace Castle
{
    const std::string toString(const int castle);
    constexpr bool    canNone (const int castle);
    constexpr bool    canE1G1 (const int castle);
    constexpr bool    canE1C1 (const int castle);
    constexpr bool    canE8G8 (const int castle);
    constexpr bool    canE8C8 (const int castle);
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline constexpr bool Castle::canNone(const int castle)
{
    return castle == Castle::None;
}

inline constexpr bool Castle::canE1G1(const int castle)
{
    return castle & Castle::E1G1;
}

inline constexpr bool Castle::canE1C1(const int castle)
{
    return castle & Castle::E1C1;
}

inline constexpr bool Castle::canE8G8(const int castle)
{
    return castle & Castle::E8G8;
}

inline constexpr bool Castle::canE8C8(const int castle)
{
    return castle & Castle::E8C8;
}

#endif  //  CASTLE_H
