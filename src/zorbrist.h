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
//  zorbrist.h
//--------------------------------------------------------------------//

#ifndef ZORBRIST_H
#define ZORBRIST_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "key.h"
#include "piece.h"
#include "square.h"

//--------------------------------------------------------------------//
//  variables
//--------------------------------------------------------------------//

namespace Zorbrist
{
    extern Key Piece    [][Piece::size()][Square::size()];
    extern Key Castle   [];
    extern Key Enpassant[];
    extern Key Depth    [];
    extern Key Side;
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

namespace Zorbrist
{
    void init();
}

#endif  //  ZORBRIST_H
