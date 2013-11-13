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
//  piece.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "piece.h"
#include "color.h"

#include <cctype>

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

int Piece::make(const char c)
{
    switch (toupper(c))
    {
        case 'P':
            return Piece::Pawn;
            break;

        case 'N':
            return Piece::Knight;
            break;

        case 'B':
            return Piece::Bishop;
            break;

        case 'R':
            return Piece::Rook;
            break;

        case 'Q':
            return Piece::Queen;
            break;

        case 'K':
            return Piece::King;
            break;

        default:
            break;
    }

    return Piece::None;
}

char Piece::toChar(const int piece, const int color)
{
    char c = ' ';

    switch (piece)
    {
        case Piece::Pawn:
            c = 'P';
            break;

        case Piece::Knight:
            c = 'N';
            break;

        case Piece::Bishop:
            c = 'B';
            break;

        case Piece::Rook:
            c = 'R';
            break;

        case Piece::Queen:
            c = 'Q';
            break;

        case Piece::King:
            c = 'K';
            break;

        default:
            break;
    }

    return Color::isWhite(color) ? c : static_cast<char>(tolower(c));
}

char Piece::toUpperChar(const int piece)
{
    return Piece::toChar(piece,Color::White);
}

char Piece::toLowerChar(const int piece)
{
    return Piece::toChar(piece,Color::Black);
}
