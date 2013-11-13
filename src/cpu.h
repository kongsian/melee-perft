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
//  cpu.h
//--------------------------------------------------------------------//

#ifndef CPU_H
#define CPU_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include <cstdint>

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

class Cpu
{
public:
    Cpu();
    bool hasPopcnt() const;

private:
    static const uint32_t Popcnt = 1 << 23;

    uint32_t m_eax;
    uint32_t m_ebx;
    uint32_t m_ecx;
    uint32_t m_edx;
};

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline Cpu::Cpu()
{
    const int eax = 1;

    __asm__("cpuid;"
            :"=a"(m_eax),           //  EAX into m_eax (output)
             "=b"(m_ebx),           //  EBX into m_ebx (output)
             "=c"(m_ecx),           //  ECX into m_ecx (output)
             "=d"(m_edx)            //  EDX into m_edx (output)
            :"a"(eax));             //  eax into EAX (input)
}

inline bool Cpu::hasPopcnt() const
{
    return m_ecx & Cpu::Popcnt;
}

#endif  //  CPU_H
