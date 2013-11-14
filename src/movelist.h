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
//  movelist.h
//--------------------------------------------------------------------//

#ifndef MOVELIST_H
#define MOVELIST_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "move.h"

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

class Movelist
{
public:
    Movelist();
    void   addMove(const int from, const int to, const int flag=0);
    void   addMove(const move_t move);
    bool   hasNext() const;
    move_t getNext();
    int    size   () const;
    void   print  () const;

private:
    move_t  m_moves[256];
    move_t* m_cur;
    move_t* m_end;
};

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline Movelist::Movelist() :
    m_cur(m_moves),
    m_end(m_moves)
{
}

inline void Movelist::addMove(const int from, const int to, const int flag)
{
    *m_end++ = Move::make(from,to,flag);
}

inline void Movelist::addMove(const move_t move)
{
    *m_end++ = move;
}

inline bool Movelist::hasNext() const
{
    return m_cur < m_end;
}

inline move_t Movelist::getNext()
{
    return *m_cur++;
}

inline int Movelist::size() const
{
    return static_cast<int>(m_end - m_moves);
}

#endif  //  MOVELIST_H
