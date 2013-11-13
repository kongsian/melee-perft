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
//  file.h
//--------------------------------------------------------------------//

#ifndef FILE_H
#define FILE_H

//--------------------------------------------------------------------//
//  constants
//--------------------------------------------------------------------//

namespace File
{
    constexpr int FileA = 0;
    constexpr int FileB = 1;
    constexpr int FileC = 2;
    constexpr int FileD = 3;
    constexpr int FileE = 4;
    constexpr int FileF = 5;
    constexpr int FileG = 6;
    constexpr int FileH = 7;
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

namespace File
{
    constexpr int  begin  ();
    constexpr int  end    ();
    constexpr int  size   ();
    constexpr int  make   (const char c);
    constexpr char toChar (const int file);
    constexpr bool isValid(const int file);
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline constexpr int File::begin()
{
    return File::FileA;
}

inline constexpr int File::end()
{
    return File::FileH + 1;
}

inline constexpr int File::size()
{
    return File::end() - File::begin();
}

inline constexpr int File::make(const char c)
{
    return c - 'a';
}

inline constexpr char File::toChar(const int file)
{
    return static_cast<char>(file + 'a');
}

inline constexpr bool File::isValid(const int file)
{
    return File::begin() <= file && file < File::end();
}

#endif  //  FILE_H
