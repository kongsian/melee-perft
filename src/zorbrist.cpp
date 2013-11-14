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
//  zorbrist.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "zorbrist.h"
#include "color.h"
#include "file.h"
#include "prng.h"
#include "square.h"

//--------------------------------------------------------------------//
//  variables
//--------------------------------------------------------------------//

namespace Zorbrist
{
    Key Piece    [Color::size()][Piece::size()][Square::size()];
    Key Castle   [16];
    Key Enpassant[File::size()];
    Key Depth    [64];
    Key Side;
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

void Zorbrist::init()
{
    Prng prng;

    //  piece

    for (auto& i : Zorbrist::Piece)
    {
        for (auto& j : i)
        {
            for (auto& k : j)
            {
                k = Key(prng.getNext(),prng.getNext());
            }
        }
    }

    //  castling

    const Key KeyE1G1(prng.getNext(),prng.getNext());
    const Key KeyE1C1(prng.getNext(),prng.getNext());
    const Key KeyE8G8(prng.getNext(),prng.getNext());
    const Key KeyE8C8(prng.getNext(),prng.getNext());

    Zorbrist::Castle[ 0] = Key(0ULL,0ULL);
    Zorbrist::Castle[ 1] = KeyE1G1;
    Zorbrist::Castle[ 2] = KeyE1C1;
    Zorbrist::Castle[ 3] = KeyE1C1 ^ KeyE1G1;
    Zorbrist::Castle[ 4] = KeyE8G8;
    Zorbrist::Castle[ 5] = KeyE8G8 ^ KeyE1G1;
    Zorbrist::Castle[ 6] = KeyE8G8 ^ KeyE1C1;
    Zorbrist::Castle[ 7] = KeyE8G8 ^ KeyE1C1 ^ KeyE1G1;
    Zorbrist::Castle[ 8] = KeyE8C8;
    Zorbrist::Castle[ 9] = KeyE8C8 ^ KeyE1G1;
    Zorbrist::Castle[10] = KeyE8C8 ^ KeyE1C1;
    Zorbrist::Castle[11] = KeyE8C8 ^ KeyE1C1 ^ KeyE1G1;
    Zorbrist::Castle[12] = KeyE8C8 ^ KeyE8G8;
    Zorbrist::Castle[13] = KeyE8C8 ^ KeyE8G8 ^ KeyE1G1;
    Zorbrist::Castle[14] = KeyE8C8 ^ KeyE8G8 ^ KeyE1C1;
    Zorbrist::Castle[15] = KeyE8C8 ^ KeyE8G8 ^ KeyE1C1 ^ KeyE1G1;

    //  enpassant

    for (auto& i : Zorbrist::Enpassant)
    {
        i = Key(prng.getNext(),prng.getNext());
    }

    //  depth

    for (auto& i : Zorbrist::Depth)
    {
        i = Key(prng.getNext(),prng.getNext());
    }

    //  side

    Zorbrist::Side = Key(prng.getNext(),prng.getNext());
}
