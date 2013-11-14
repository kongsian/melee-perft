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
//  option.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "option.h"
#include "board.h"

#include <algorithm>
#include <cstdlib>
#include <getopt.h>
#include <iostream>

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

Option::Option(const int argc, char* const argv[]) :
    fen    (Board::StartFen),
    depth  (0),
    hash   (0),
    threads(1)
{
    const option longOptions[] =
    {
        {"fen",     required_argument,  0,  'f'},
        {"depth",   required_argument,  0,  'd'},
        {"hash",    required_argument,  0,  'h'},
        {"threads", required_argument,  0,  't'},
        {0, 0, 0, 0}
    };
    const char* shortOptions = "f:d:h:t:";
    int optionIndex = 0;

    while (true)
    {
        int c = getopt_long(argc,argv,shortOptions,longOptions,&optionIndex);

        if (c == -1)
        {
            break;
        }

        switch (c)
        {
            case 'f':
                fen = optarg;
                break;

            case 'd':
                depth = atoi(optarg);
                break;

            case 'h':
                hash = atoi(optarg);
                break;

            case 't':
                threads = std::max(atoi(optarg),1);
                break;

            default:
                break;
        }
    }
}

void Option::help()
{
    std::cout << "melee-perft --fen <string> --depth <depth> --hash <sizeMB> --threads <num>\n";
    std::cout << "If fen string is omitted, the start position is used."
              << std::endl;
}
