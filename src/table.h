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
//  table.h
//--------------------------------------------------------------------//

#ifndef TABLE_H
#define TABLE_H

//--------------------------------------------------------------------//
//  includes
//-------------------------------------------------------------------//

#include "key.h"

#include <cstdint>
#include <memory>

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

class Table
{
public:
    Table();

    void alloc(const int size_mb);
    int  size () const;
    void store(const Key& key, const uint64_t nodes);
    bool probe(const Key& key, uint64_t& nodes) const;

private:
    struct Slot
    {
        uint64_t hikey;
        uint64_t nodes;
    };

    static constexpr int SlotSize = static_cast<int>(sizeof(Slot));

    bool     m_inuse;
    int      m_size;
    int64_t  m_total;
    std::unique_ptr<Slot[]> m_table;
};

//--------------------------------------------------------------------//
//  variables
//-------------------------------------------------------------------//

extern Table table;

#endif  //  TABLE_H
