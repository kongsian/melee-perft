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
//  genleaf.h
//--------------------------------------------------------------------//

#ifndef GENLEAF_H
#define GENLEAF_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "bit.h"

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

class Attack;
class Board;

class Genleaf
{
public:
    Genleaf(const Attack& attack, const Board& board);
    int size() const;

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
    void addPawnMoves    (const bit_t moves, const int delta);
    void knight          ();
    void bishop          ();
    void rook            ();
    void queen           ();
    void king            ();
    void castle          ();
    void castleWhite     ();
    void castleBlack     ();

    const Attack& m_attack;
    const Board&  m_board;
    int           m_size;
    int           m_king;
    bit_t         m_all;
    bit_t         m_target;
};

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline int Genleaf::size() const
{
    return m_size;
}

#endif  //  GENLEAF_H
