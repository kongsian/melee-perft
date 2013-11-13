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
//  move.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "move.h"
#include "piece.h"
#include "square.h"

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

const std::string Move::toString(const move_t move)
{
    std::string s;

    //  from square

    const int from = Move::from(move);
    s += Square::toString(from);

    //  to square

    const int to = Move::to(move);
    s += Square::toString(to);

    //  promotion

    if (Move::isPromote(move))
    {
        const int promote = Move::promote(move);
        s += Piece::toLowerChar(promote);
    }

    return s;
}
