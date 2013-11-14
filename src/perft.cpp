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
//  perft.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "perft.h"
#include "attack.h"
#include "board.h"
#include "clock.h"
#include "gen.h"
#include "genleaf.h"
#include "move.h"
#include "table.h"
#include "zorbrist.h"

#include <cstdint>
#include <iostream>

//--------------------------------------------------------------------//
//  variables
//--------------------------------------------------------------------//

namespace
{
    Table table;
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

namespace
{
    uint64_t node(Board& board, const int depth);
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

void Perft::root(const std::string& fen, const int depth, const int size)
{
    Clock clock;
    table.alloc(size);

    std::cout << "Table: "
              << table.size()
              << " MB\n";
    std::cout << "Depth: "
              << depth
              << std::endl;

    Board board(fen);
    board.print();

    Attack attack(board);
    Gen gen(attack,board);

    uint64_t total_nodes = 0ULL;
    Board::Undo undo;
    while (gen.hasNext())
    {
        const move_t move = gen.getNext();
        uint64_t nodes = 1;

        if (depth > 1)
        {
            board.moveDo(move,undo);
            nodes = node(board,depth-1);
            board.moveUndo(move,undo);
        }

        total_nodes += nodes;
        std::cout << Move::toString(move)
                  << '\t'
                  << nodes
                  << std::endl;
    }

    const double etime = static_cast<double>(clock.elapsed()) / 1000.0;

    std::cout << "NODES "
              << total_nodes
              << std::endl;
    std::cout << "ETIME "
              << etime
              << " secs"
              << std::endl;
}

namespace
{
    uint64_t node(Board& board, const int depth)
    {
        //  frontier

        if (depth == 1)
        {
            Attack attack(board);
            Genleaf gen(attack,board);
            return gen.size();
        }

        //  probe table

        uint64_t nodes = 0ULL;
        Key key = board.getKey() ^ Zorbrist::Depth[depth];
        if (table.probe(key,nodes))
        {
            return nodes;
        }

        Attack attack(board);
        Gen gen(attack,board);

        Board::Undo undo;
        while (gen.hasNext())
        {
            const move_t move = gen.getNext();
            board.moveDo(move,undo);
            nodes += node(board,depth-1);
            board.moveUndo(move,undo);
        }

        table.store(key,nodes);
        return nodes;
    }
}
