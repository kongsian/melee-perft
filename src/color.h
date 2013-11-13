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
//  color.h
//--------------------------------------------------------------------//

#ifndef COLOR_H
#define COLOR_H

//--------------------------------------------------------------------//
//  constants
//--------------------------------------------------------------------//

namespace Color
{
    constexpr int White = 0;
    constexpr int Black = 1;
    constexpr int None  = 2;
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

namespace Color
{
    constexpr int  begin   ();
    constexpr int  end     ();
    constexpr int  size    ();
    constexpr int  make    (const char c);
    constexpr char toChar  (const int color);
    constexpr bool isWhite (const int color);
    constexpr bool isBlack (const int color);
    constexpr bool isValid (const int color);
    constexpr int  opposite(const int color);
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline constexpr int Color::begin()
{
    return Color::White;
}

inline constexpr int Color::end()
{
    return Color::Black + 1;
}

inline constexpr int Color::size()
{
    return Color::end() - Color::begin();
}

inline constexpr int Color::make(const char c)
{
    return c == 'w' ? Color::White : (c == 'b' ? Color::Black : Color::None);
}

inline constexpr char Color::toChar(const int color)
{
    return Color::isWhite(color) ? 'w' : (Color::isBlack(color) ? 'b' : ' ');
}

inline constexpr bool Color::isWhite(const int color)
{
    return color == Color::White;
}

inline constexpr bool Color::isBlack(const int color)
{
    return color == Color::Black;
}

inline constexpr bool Color::isValid(const int color)
{
    return Color::begin() <= color && color < Color::end();
}

inline constexpr int Color::opposite(const int color)
{
    return color ^ Color::White ^ Color::Black;
}

#endif  //  COLOR_H
