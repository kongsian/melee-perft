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
//  bit_enumerator.h
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  This class generates all possible bit combinations of a given
//  bitboard mask.
//  For e.g. given a mask with A1,B1 bits set, it will generate
//  {}, {A1}, {B1}, {A1,B1} with each successive call.
//
//  Bit::Enumerator be(mask);
//  while (be.hasNext()) {
//      const bit_t b = be.getNext();
//  }
//--------------------------------------------------------------------//

#ifndef BIT_ENUMERATOR_H
#define BIT_ENUMERATOR_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "bit.h"

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

namespace Bit
{
    class Enumerator
    {
    public:
        explicit Enumerator(const bit_t mask);
        bool  hasNext() const;
        bit_t getNext();

    private:
        bit_t m_mask;       //  bit mask to enumerate 
        int   m_count;      //  current count
        int   m_total;      //  total possible enumerations
    };
}

#endif  //  BIT_ENUMERATOR_H
