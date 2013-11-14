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
//  gen.h
//--------------------------------------------------------------------//

#ifndef GEN_H
#define GEN_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "bit.h"
#include "movelist.h"

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

class Attack;
class Board;

class Gen
{
public:
    Gen(const Attack& attack, const Board& board);

    bool   hasNext() const;
    move_t getNext();
    int    size   () const;
    void   print  () const;

private:
    void legal           ();
    void evasion         ();
    void pawnAdvance     ();
    void pawnAdvanceWhite();
    void pawnAdvanceBlack();
    void pawnCapture     ();
    void pawnCaptureWhite();
    void pawnCaptureBlack();
    void enpassant       ();
    void addPawnMoves    (const bit_t moves, const int delta, const int flag=0);
    void addPieceMoves   (const int from, const bit_t moves);
    void knight          ();
    void bishop          ();
    void rook            ();
    void queen           ();
    void king            ();
    void castle          ();
    void castleWhite     ();
    void castleBlack     ();

    Movelist      m_movelist;
    const Attack& m_attack;
    const Board&  m_board;
    int           m_king;
    bit_t         m_all;
    bit_t         m_target;
};

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline bool Gen::hasNext() const
{
    return m_movelist.hasNext();
}

inline move_t Gen::getNext()
{
    return m_movelist.getNext();
}

inline int Gen::size() const
{
    return m_movelist.size();
}

inline void Gen::print() const
{
    m_movelist.print();
}

inline void Gen::addPieceMoves(const int from, bit_t moves)
{
    while (moves)
    {
        const int to = Bit::pop(moves);
        m_movelist.addMove(from,to);
    }
}

#endif  //  GEN_H
