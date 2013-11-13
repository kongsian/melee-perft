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
//  attack.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "attack.h"
#include "board.h"

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

Attack::Attack(const Board& board) :
    m_attack(generateAttack(board)),
    m_pinned(generatePinned(board))
{
}

bit_t Attack::generateAttack(const Board& board) const
{
    //  Mask out the king to simplify check evasion moves.
    //  In this way, the king cannot escape from check by
    //  running into its "shadow".

    const bit_t all = board.getAll() ^ board.getMyKings();
    bit_t attack    = 0ULL;
    bit_t b         = 0ULL;

    b = board.getOpPawns();
    attack |= board.isWhiteToMove() ?
           (Bit::shiftNegative07(b) | Bit::shiftNegative09(b)) :
           (Bit::shiftPositive07(b) | Bit::shiftPositive09(b));

    b = board.getOpKnights();
    while (b)
    {
        const int square = Bit::pop(b);
        attack |= knight(square);
    }

    b = board.getOpBishopQueens();
    while (b)
    {
        const int square = Bit::pop(b);
        attack |= bishop(square,all);
    }

    b = board.getOpRookQueens();
    while (b)
    {
        const int square = Bit::pop(b);
        attack |= rook(square,all);
    }

    attack |= king(board.getOpKing());

    return attack;
}

bit_t Attack::generatePinned(const Board& board) const
{
    const int myKing = board.getMyKing();
    bit_t pinners    = (board.getOpBishopQueens() & Bit::Bishop[myKing]) |
                       (board.getOpRookQueens  () & Bit::Rook  [myKing]);

    bit_t pinned = 0ULL;
    if (pinners)
    {
        const bit_t all = board.getAll();
        const bit_t occ = queen(myKing,all) & board.getMyOcc();
        pinners &= queen(myKing,all^occ);

        while (pinners)
        {
            const int square = Bit::pop(pinners);
            pinned |= Bit::Sray[myKing][square] & occ;
        }
    }

    return pinned;
}
