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
//  clock.h
//--------------------------------------------------------------------//

#ifndef CLOCK_H
#define CLOCK_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include <chrono>
#include <cstdint>

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

class Clock
{
public:
    Clock();

    void reset();
    uint64_t elapsed();

private:
    std::chrono::high_resolution_clock::time_point m_start;
};

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline Clock::Clock()
{
    reset();
}

inline void Clock::reset()
{
    m_start = std::chrono::high_resolution_clock::now();
}

inline uint64_t Clock::elapsed()
{
    const auto now = std::chrono::high_resolution_clock::now();
    return (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start)).count();
}

#endif  //  CLOCK_H
