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
//  board.h
//--------------------------------------------------------------------//

#ifndef BOARD_H
#define BOARD_H

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "bit.h"
#include "castle.h"
#include "color.h"
#include "piece.h"
#include "square.h"

#include <string>

//--------------------------------------------------------------------//
//  types
//--------------------------------------------------------------------//

class Board
{
public:
    static const std::string StartFen;
    static const std::string KiwiPete;

    Board();
    explicit Board(const std::string& fen);
    explicit Board(const Board& board);

    void   print            () const;
    int    getPiece         (const int square) const;
    int    getColor         (const int square) const;
    int    getMyKing        () const;
    int    getOpKing        () const;
    int    getMe            () const;
    int    getOp            () const;
    int    getEnpassant     () const;
    bool   isWhiteToMove    () const;
    bool   isBlackToMove    () const;
    bool   canCastleNone    () const;
    bool   canCastleE1G1    () const;
    bool   canCastleE1C1    () const;
    bool   canCastleE8G8    () const;
    bool   canCastleE8C8    () const;

    bit_t  getMyPawns       () const;
    bit_t  getOpPawns       () const;
    bit_t  getMyKnights     () const;
    bit_t  getOpKnights     () const;
    bit_t  getMyBishops     () const;
    bit_t  getOpBishops     () const;
    bit_t  getMyRooks       () const;
    bit_t  getOpRooks       () const;
    bit_t  getMyQueens      () const;
    bit_t  getOpQueens      () const;
    bit_t  getMyKings       () const;
    bit_t  getOpKings       () const;
    bit_t  getMyBishopQueens() const;
    bit_t  getOpBishopQueens() const;
    bit_t  getMyRookQueens  () const;
    bit_t  getOpRookQueens  () const;
    bit_t  getMyOcc         () const;
    bit_t  getOpOcc         () const;
    bit_t  getAll           () const;

private:
    void   clear            ();
    void   fromFen          (const std::string& fen);
    const  std::string toFen() const;

    int    m_piece[Square::size()];     //  piece on square
    int    m_king [Color::size()];      //  location of kings
    int    m_me;                        //  side to move
    int    m_op;                        //  opposite side
    int    m_castle;                    //  castling flag
    int    m_enpassant;                 //  enpassant square

    bit_t  m_pieces[Color::size()][Piece::size()];
    bit_t  m_occ   [Color::size()];
    bit_t  m_all;
    bit_t* m_pieces_me;
    bit_t* m_pieces_op;
};

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

inline int Board::getPiece(const int square) const
{
    return m_piece[square];
}

inline int Board::getColor(const int square) const
{
    return Bit::test(m_occ[Color::White],square) ? Color::White :
          (Bit::test(m_occ[Color::Black],square) ? Color::Black : Color::None);
}

inline int Board::getMyKing() const
{
    return m_king[m_me];
}

inline int Board::getOpKing() const
{
    return m_king[m_op];
}

inline int Board::getMe() const
{
    return m_me;
}

inline int Board::getOp() const
{
    return m_op;
}

inline int Board::getEnpassant() const
{
    return m_enpassant;
}

inline bool Board::isWhiteToMove() const
{
    return Color::isWhite(m_me);
}

inline bool Board::isBlackToMove() const
{
    return Color::isBlack(m_me);
}

inline bool Board::canCastleNone() const
{
    return Castle::canNone(m_castle);
}

inline bool Board::canCastleE1G1() const
{
    return Castle::canE1G1(m_castle);
}

inline bool Board::canCastleE1C1() const
{
    return Castle::canE1C1(m_castle);
}

inline bool Board::canCastleE8G8() const
{
    return Castle::canE8G8(m_castle);
}

inline bool Board::canCastleE8C8() const
{
    return Castle::canE8C8(m_castle);
}

inline bit_t Board::getMyPawns() const
{
    return m_pieces_me[Piece::Pawn];
}

inline bit_t Board::getOpPawns() const
{
    return m_pieces_op[Piece::Pawn];
}

inline bit_t Board::getMyKnights() const
{
    return m_pieces_me[Piece::Knight];
}

inline bit_t Board::getOpKnights() const
{
    return m_pieces_op[Piece::Knight];
}

inline bit_t Board::getMyBishops() const
{
    return m_pieces_me[Piece::Bishop];
}

inline bit_t Board::getOpBishops() const
{
    return m_pieces_op[Piece::Bishop];
}

inline bit_t Board::getMyRooks() const
{
    return m_pieces_me[Piece::Rook];
}

inline bit_t Board::getOpRooks() const
{
    return m_pieces_op[Piece::Rook];
}

inline bit_t Board::getMyQueens() const
{
    return m_pieces_me[Piece::Queen];
}

inline bit_t Board::getOpQueens() const
{
    return m_pieces_op[Piece::Queen];
}

inline bit_t Board::getMyKings() const
{
    return m_pieces_me[Piece::King];
}

inline bit_t Board::getOpKings() const
{
    return m_pieces_op[Piece::King];
}

inline bit_t Board::getMyBishopQueens() const
{
    return m_pieces_me[Piece::Bishop] | m_pieces_me[Piece::Queen];
}

inline bit_t Board::getOpBishopQueens() const
{
    return m_pieces_op[Piece::Bishop] | m_pieces_op[Piece::Queen];
}

inline bit_t Board::getMyRookQueens() const
{
    return m_pieces_me[Piece::Rook] | m_pieces_me[Piece::Queen];
}

inline bit_t Board::getOpRookQueens() const
{
    return m_pieces_op[Piece::Rook] | m_pieces_op[Piece::Queen];
}

inline bit_t Board::getMyOcc() const
{
    return m_occ[m_me];
}

inline bit_t Board::getOpOcc() const
{
    return m_occ[m_op];
}

inline bit_t Board::getAll() const
{
    return m_all;
}

#endif  //  BOARD_H
