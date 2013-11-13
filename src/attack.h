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
//  attack.h
//--------------------------------------------------------------------//

#ifndef ATTACK_H
#define ATTACK_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "bit.h"
#include "magic.h"

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

class Board;

class Attack
{
public:
    explicit Attack(const Board& board);

    bit_t getAttack() const;
    bit_t getPinned() const;
    bool  isAttack (const int square) const;
    bool  isPinned (const int square) const;

    static bit_t pawn  (const int square, const int color);
    static bit_t knight(const int square);
    static bit_t king  (const int square);
    static bit_t bishop(const int square, const bit_t all);
    static bit_t rook  (const int square, const bit_t all);
    static bit_t queen (const int square, const bit_t all);

private:
    bit_t generateAttack(const Board& board) const;
    bit_t generatePinned(const Board& board) const;

    bit_t m_attack;
    bit_t m_pinned;
};

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline bit_t Attack::getAttack() const
{
    return m_attack;
}

inline bit_t Attack::getPinned() const
{
    return m_pinned;
}

inline bool Attack::isAttack(const int square) const
{
    return Bit::test(m_attack,square);
}

inline bool Attack::isPinned(const int square) const
{
    return Bit::test(m_pinned,square);
}

inline bit_t Attack::pawn(const int square, const int color)
{
    return Bit::Pawn[color][square];
}

inline bit_t Attack::knight(const int square)
{
    return Bit::Knight[square];
}

inline bit_t Attack::king(const int square)
{
    return Bit::King[square];
}

inline bit_t Attack::bishop(const int square, const bit_t all)
{
    const auto& m = Magic::Bishop[square];
    return m.ptr[((all & m.mask) * m.magic) >> m.shift];
}

inline bit_t Attack::rook(const int square, const bit_t all)
{
    const auto& m = Magic::Rook[square];
    return m.ptr[((all & m.mask) * m.magic) >> m.shift];
}

inline bit_t Attack::queen(const int square, const bit_t all)
{
    return bishop(square,all) | rook(square,all);
}

#endif  //  ATTACK_H
