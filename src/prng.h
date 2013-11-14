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
//  prng.h
//--------------------------------------------------------------------//

#ifndef PRNG_H
#define PRNG_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include <cstdint>

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

class Prng
{
public:
    Prng();
    uint64_t getNext();

private:
    static uint64_t m_x;
    static uint64_t m_c;
    static uint64_t m_y;
    static uint64_t m_z;

    uint64_t mwc();
    uint64_t xsh();
    uint64_t cng();
};

#endif  //  PRNG_H
