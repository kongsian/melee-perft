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
//  main.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "bit.h"
#include "board.h"
#include "magic.h"
#include "option.h"
#include "perft.h"
#include "program.h"
#include "table.h"
#include "zorbrist.h"

#include <iostream>

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

int main(int argc, char* argv[])
{
    std::cout << Program::Name
              << ' '
              << Program::Version
              << " by "
              << Program::Author
              << std::endl;

    //  inits

    Bit::init     ();
    Magic::init   ();
    Zorbrist::init();

    //  arguments

    Option option(argc,argv);
    table.alloc(option.hash);

    std::cout << "Table: "
              << table.size()
              << " MB\n";
    std::cout << "Threads: "
              << option.threads
              << '\n';

    Perft::root(option);
}
