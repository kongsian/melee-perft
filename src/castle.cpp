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
//  castle.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "castle.h"

#include <string>

//--------------------------------------------------------------------//
//  constants
//--------------------------------------------------------------------//

namespace
{
    const std::string Notation[] =
    {
        "-" , "K"  , "Q"  , "KQ"  ,
        "k" , "Kk" , "Qk" , "KQk" ,
        "q" , "Kq" , "Qq" , "KQq" ,
        "kq", "Kkq", "Qkq", "KQkq",
    };
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

const std::string Castle::toString(const int castle)
{
    return Notation[castle];
}
