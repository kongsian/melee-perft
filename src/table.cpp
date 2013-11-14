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
//  table.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  This implements a lockless transposition table.
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "table.h"

#include <iostream>

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

Table::Table() :
    m_inuse(false),
    m_size (0),
    m_total(0)
{
}

void Table::alloc(const int size_mb)
{
    if (size_mb == 0)
    {
        return;
    }

    //  calculate number of slots

    const int64_t slot_max = (size_mb / SlotSize) << 20;
    for (m_total = 1; m_total <= slot_max / 2; m_total *= 2);
    m_size = static_cast<int>(m_total >> 20) * SlotSize;

    //  allocate
 
    auto* p = new(std::nothrow) Slot[m_total];
    if (!p)
    {
        std::cout << "Cannot allocate hash table."
                  << std::endl;
        return;
    }

    m_table.reset(p);
    m_inuse = true;
}

int Table::size() const
{
    return m_size;
}

//  The first slot is a nodes first replacement.
//  The second slot is an always replace.

void Table::store(const Key& key, const uint64_t nodes)
{
    if (m_inuse)
    {
        const uint64_t hikey = key.getHi();
        const uint64_t lokey = key.getLo();

        Slot* p = m_table.get() + (lokey & (m_total - 2));
        if (nodes < p->nodes)
        {
            ++p;
        }
        p->hikey = hikey ^ nodes;
        p->nodes = nodes;
    }
}

bool Table::probe(const Key& key, uint64_t& nodes) const
{
    if (m_inuse)
    {
        const uint64_t hikey = key.getHi();
        const uint64_t lokey = key.getLo();
        const Slot* p        = m_table.get() + (lokey & (m_total - 2));

        //  first slot
 
        if (hikey == (p->hikey ^ p->nodes))
        {
            nodes = p->nodes;
            return true;
        }

        //  second slot

        ++p;
        if (hikey == (p->hikey ^ p->nodes))
        {
            nodes = p->nodes;
            return true;
        }
    }

    nodes = 0ULL;
    return false;
}
