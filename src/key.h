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
//  key.h
//--------------------------------------------------------------------//

#ifndef KEY_H
#define KEY_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include <cstdint>

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

class Key
{
public:
    Key();
    Key(uint64_t hi, uint64_t lo);

    uint64_t getHi() const;
    uint64_t getLo() const;

          Key& operator =(const Key& key);
          Key& operator^=(const Key& key);
    const Key  operator^ (const Key& key) const;
    bool       operator==(const Key& key) const;

private:
    uint64_t m_hi;
    uint64_t m_lo;
};

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline Key::Key():
    m_hi(0ULL),
    m_lo(0ULL)
{
}

inline Key::Key(uint64_t hi, uint64_t lo) :
    m_hi(hi),
    m_lo(lo)
{
}

inline uint64_t Key::getHi() const
{
    return m_hi;
}

inline uint64_t Key::getLo() const
{
    return m_lo;
}

inline Key& Key::operator=(const Key& key)
{
    m_hi = key.m_hi;
    m_lo = key.m_lo;
    return *this;
}

inline Key& Key::operator^=(const Key& key)
{
    m_hi ^= key.m_hi;
    m_lo ^= key.m_lo;
    return *this;
}

inline const Key Key::operator^(const Key& key) const
{
    return Key(m_hi ^ key.m_hi, m_lo ^ key.m_lo);
}

inline bool Key::operator==(const Key& key) const
{
    return m_hi == key.m_hi && m_lo == key.m_lo;
}

#endif  //  KEY_H
