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
//  bit_enumerator.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "bit_enumerator.h"

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

Bit::Enumerator::Enumerator(const bit_t mask) :
    m_mask (mask),
    m_count(0),
    m_total(1 << Bit::count(mask))
{
}

bool Bit::Enumerator::hasNext() const
{
    return m_count < m_total;
}

bit_t Bit::Enumerator::getNext()
{
    bit_t b = 0ULL;
    bit_t m = m_mask;
    int i   = 1;

    while (m)
    {
        const bit_t c = m & -m;
        m ^= c;

        if (i & m_count)
        {
            b |= c;
        }
        i <<= 1;
    }
    ++m_count;

    return b;
}
