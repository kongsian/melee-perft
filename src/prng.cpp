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
//  prng.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  The following algorithm is from George Marsaglia.
//  www.velocityreviews.com/forums/t673657-64-bit-kiss-rngs.html.
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "prng.h"

//--------------------------------------------------------------------//
//  data
//--------------------------------------------------------------------//

uint64_t Prng::m_x = 1234567890987654321ULL;
uint64_t Prng::m_c = 123456123456123456ULL;
uint64_t Prng::m_y = 362436362436362436ULL;
uint64_t Prng::m_z = 1066149217761810ULL;

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

Prng::Prng()
{
}

uint64_t Prng::getNext()
{
    return mwc() + xsh() + cng();
}

//  multiply with carry

uint64_t Prng::mwc()
{
    const uint64_t t = (m_x << 58) + m_c;
    m_c  = m_x >> 6;
    m_x += t;
    m_c += (m_x < t ? 1 : 0);
    return m_x;
}

//  xor shift

uint64_t Prng::xsh()
{
    m_y ^= m_y << 13;
    m_y ^= m_y >> 17;
    m_y ^= m_y << 43;
    return m_y;
}

//  congruential

uint64_t Prng::cng()
{
    m_z = 6906969069ULL * m_z + 1234567ULL;
    return m_z;
}
