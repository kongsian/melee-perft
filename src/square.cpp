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
//  square.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "square.h"
#include "file.h"
#include "rank.h"

#include <string>

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

int Square::make(const std::string& s)
{
    if (s.size() == 2)
    {
        const int rank = Rank::make(s[1]);
        const int file = File::make(s[0]);

        if (Rank::isValid(rank)
        &&  File::isValid(file))
        {
            return Square::make(rank,file);
        }
    }

    return Square::None;
}

const std::string Square::toString(const int square)
{
    if (Square::isValid(square))
    {
        std::string s;
        s += File::toChar(Square::file(square));
        s += Rank::toChar(Square::rank(square));
        return s;
    }

    return "-";
}
