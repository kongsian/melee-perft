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
//  magic.cpp
//--------------------------------------------------------------------//

//--------------------------------------------------------------------//
//  includes
//--------------------------------------------------------------------//

#include "magic.h"
#include "bit_enumerator.h"
#include "square.h"

#include <memory>

//--------------------------------------------------------------------//
//  variables
//--------------------------------------------------------------------//

namespace Magic
{
    Magic::magic_t Bishop[]=
    {
        { 0x144014018c004080ULL, 0x0040201008040200ULL, nullptr, 58 },
        { 0x0028010800810002ULL, 0x0000402010080400ULL, nullptr, 59 },
        { 0x0210410208a55ea0ULL, 0x0000004020100a00ULL, nullptr, 59 },
        { 0x8014051204914001ULL, 0x0000000040221400ULL, nullptr, 59 },
        { 0x2004046020880200ULL, 0x0000000002442800ULL, nullptr, 59 },
        { 0x0801040340c04000ULL, 0x0000000204085000ULL, nullptr, 59 },
        { 0x8406060104c10801ULL, 0x0000020408102000ULL, nullptr, 59 },
        { 0x000016080c120801ULL, 0x0002040810204000ULL, nullptr, 58 },
        { 0x004128e008008504ULL, 0x0020100804020000ULL, nullptr, 59 },
        { 0x1400201104092440ULL, 0x0040201008040000ULL, nullptr, 59 },
        { 0x0000222811012110ULL, 0x00004020100a0000ULL, nullptr, 59 },
        { 0x4180041400800008ULL, 0x0000004022140000ULL, nullptr, 59 },
        { 0x80014c0308880090ULL, 0x0000000244280000ULL, nullptr, 59 },
        { 0x2032020110080000ULL, 0x0000020408500000ULL, nullptr, 59 },
        { 0x1224010108024000ULL, 0x0002040810200000ULL, nullptr, 59 },
        { 0x0802a10402920840ULL, 0x0004081020400000ULL, nullptr, 59 },
        { 0x02c0084d28182104ULL, 0x0010080402000200ULL, nullptr, 59 },
        { 0x4022002002043100ULL, 0x0020100804000400ULL, nullptr, 59 },
        { 0x0110045820802008ULL, 0x004020100a000a00ULL, nullptr, 57 },
        { 0x3002001040524018ULL, 0x0000402214001400ULL, nullptr, 57 },
        { 0x22c0800c00a04004ULL, 0x0000024428002800ULL, nullptr, 57 },
        { 0x1200200200b00800ULL, 0x0002040850005000ULL, nullptr, 57 },
        { 0x0812040082012002ULL, 0x0004081020002000ULL, nullptr, 59 },
        { 0x0102082841040105ULL, 0x0008102040004000ULL, nullptr, 59 },
        { 0x0820090504188800ULL, 0x0008040200020400ULL, nullptr, 59 },
        { 0x5009100004505201ULL, 0x0010080400040800ULL, nullptr, 59 },
        { 0x8100860090006a00ULL, 0x0020100a000a1000ULL, nullptr, 57 },
        { 0x12500402204010a0ULL, 0x0040221400142200ULL, nullptr, 55 },
        { 0x804501000090400cULL, 0x0002442800284400ULL, nullptr, 55 },
        { 0x02080a0004220109ULL, 0x0004085000500800ULL, nullptr, 57 },
        { 0x000204000a110702ULL, 0x0008102000201000ULL, nullptr, 59 },
        { 0x0044010200228200ULL, 0x0010204000402000ULL, nullptr, 59 },
        { 0x1032201400220800ULL, 0x0004020002040800ULL, nullptr, 59 },
        { 0x0682482400a00131ULL, 0x0008040004081000ULL, nullptr, 59 },
        { 0x0304006402080444ULL, 0x00100a000a102000ULL, nullptr, 57 },
        { 0x80830a0081080080ULL, 0x0022140014224000ULL, nullptr, 55 },
        { 0x14080a0400049100ULL, 0x0044280028440200ULL, nullptr, 55 },
        { 0x0004180201002081ULL, 0x0008500050080400ULL, nullptr, 57 },
        { 0x4004610402004429ULL, 0x0010200020100800ULL, nullptr, 59 },
        { 0x00042100a00200a1ULL, 0x0020400040201000ULL, nullptr, 59 },
        { 0x0c04040440000c22ULL, 0x0002000204081000ULL, nullptr, 59 },
        { 0x00010405200c8409ULL, 0x0004000408102000ULL, nullptr, 59 },
        { 0x1200b201030a1000ULL, 0x000a000a10204000ULL, nullptr, 57 },
        { 0x0000001148000c01ULL, 0x0014001422400000ULL, nullptr, 57 },
        { 0x020140220a000420ULL, 0x0028002844020000ULL, nullptr, 57 },
        { 0x0040010401000120ULL, 0x0050005008040200ULL, nullptr, 57 },
        { 0x1015103c02420d02ULL, 0x0020002010080400ULL, nullptr, 59 },
        { 0x009204190200a034ULL, 0x0040004020100800ULL, nullptr, 59 },
        { 0x0002120960088200ULL, 0x0000020408102000ULL, nullptr, 59 },
        { 0x080224010410c18cULL, 0x0000040810204000ULL, nullptr, 59 },
        { 0x0000010041104100ULL, 0x00000a1020400000ULL, nullptr, 59 },
        { 0x0080800420880000ULL, 0x0000142240000000ULL, nullptr, 59 },
        { 0x024400200c240000ULL, 0x0000284402000000ULL, nullptr, 59 },
        { 0x2004600401220004ULL, 0x0000500804020000ULL, nullptr, 59 },
        { 0x000420080b030000ULL, 0x0000201008040200ULL, nullptr, 59 },
        { 0x242a682514028100ULL, 0x0000402010080400ULL, nullptr, 59 },
        { 0x1052004100882114ULL, 0x0002040810204000ULL, nullptr, 58 },
        { 0x0400310888010880ULL, 0x0004081020400000ULL, nullptr, 59 },
        { 0x80b0000200940400ULL, 0x000a102040000000ULL, nullptr, 59 },
        { 0x00090000a0940408ULL, 0x0014224000000000ULL, nullptr, 59 },
        { 0x0010020408902400ULL, 0x0028440200000000ULL, nullptr, 59 },
        { 0x300000c010410240ULL, 0x0050080402000000ULL, nullptr, 59 },
        { 0x001820220c082892ULL, 0x0020100804020000ULL, nullptr, 59 },
        { 0x0250201094045340ULL, 0x0040201008040200ULL, nullptr, 58 },
    };

    Magic::magic_t Rook[]=
    {
        { 0x1080044008108020ULL, 0x000101010101017eULL, nullptr, 52 },
        { 0x0040041004200442ULL, 0x000202020202027cULL, nullptr, 53 },
        { 0x010029001040a000ULL, 0x000404040404047aULL, nullptr, 53 },
        { 0x4880080180041000ULL, 0x0008080808080876ULL, nullptr, 53 },
        { 0x1080080080840006ULL, 0x001010101010106eULL, nullptr, 53 },
        { 0x0080040022008001ULL, 0x002020202020205eULL, nullptr, 53 },
        { 0x2400081884011022ULL, 0x004040404040403eULL, nullptr, 53 },
        { 0x0200022404428605ULL, 0x008080808080807eULL, nullptr, 52 },
        { 0x20148000c0002180ULL, 0x0001010101017e00ULL, nullptr, 53 },
        { 0x0412802000400084ULL, 0x0002020202027c00ULL, nullptr, 54 },
        { 0x000a0010208204c0ULL, 0x0004040404047a00ULL, nullptr, 54 },
        { 0x0040802804801000ULL, 0x0008080808087600ULL, nullptr, 54 },
        { 0x0a00802400803800ULL, 0x0010101010106e00ULL, nullptr, 54 },
        { 0x2809000b00040008ULL, 0x0020202020205e00ULL, nullptr, 54 },
        { 0x0081000100440200ULL, 0x0040404040403e00ULL, nullptr, 54 },
        { 0x0140800840802100ULL, 0x0080808080807e00ULL, nullptr, 53 },
        { 0x2200208002804000ULL, 0x00010101017e0100ULL, nullptr, 53 },
        { 0x00c7020022074086ULL, 0x00020202027c0200ULL, nullptr, 54 },
        { 0x8011410060001100ULL, 0x00040404047a0400ULL, nullptr, 54 },
        { 0x1002020010082040ULL, 0x0008080808760800ULL, nullptr, 54 },
        { 0x40400d0011780100ULL, 0x00101010106e1000ULL, nullptr, 54 },
        { 0x0000808002000400ULL, 0x00202020205e2000ULL, nullptr, 54 },
        { 0x01040b0100020004ULL, 0x00404040403e4000ULL, nullptr, 54 },
        { 0x0000020004008047ULL, 0x00808080807e8000ULL, nullptr, 53 },
        { 0x480140008002a084ULL, 0x000101017e010100ULL, nullptr, 53 },
        { 0x08002000c0015008ULL, 0x000202027c020200ULL, nullptr, 54 },
        { 0x2804208200124200ULL, 0x000404047a040400ULL, nullptr, 54 },
        { 0x0240300080800800ULL, 0x0008080876080800ULL, nullptr, 54 },
        { 0x2023080080140080ULL, 0x001010106e101000ULL, nullptr, 54 },
        { 0x0040240080420080ULL, 0x002020205e202000ULL, nullptr, 54 },
        { 0x8008020400012830ULL, 0x004040403e404000ULL, nullptr, 54 },
        { 0x0000408200240051ULL, 0x008080807e808000ULL, nullptr, 53 },
        { 0x8000400120800084ULL, 0x0001017e01010100ULL, nullptr, 53 },
        { 0x1008810021004000ULL, 0x0002027c02020200ULL, nullptr, 54 },
        { 0x9002441501002001ULL, 0x0004047a04040400ULL, nullptr, 54 },
        { 0x4101500080800800ULL, 0x0008087608080800ULL, nullptr, 54 },
        { 0x0738008400800980ULL, 0x0010106e10101000ULL, nullptr, 54 },
        { 0x0022000802000410ULL, 0x0020205e20202000ULL, nullptr, 54 },
        { 0x0000108904000812ULL, 0x0040403e40404000ULL, nullptr, 54 },
        { 0x4810010062000084ULL, 0x0080807e80808000ULL, nullptr, 53 },
        { 0x0011400880208000ULL, 0x00017e0101010100ULL, nullptr, 53 },
        { 0x0120904001010020ULL, 0x00027c0202020200ULL, nullptr, 54 },
        { 0x1408410020010010ULL, 0x00047a0404040400ULL, nullptr, 54 },
        { 0x2002180010008080ULL, 0x0008760808080800ULL, nullptr, 54 },
        { 0x001102108801000cULL, 0x00106e1010101000ULL, nullptr, 54 },
        { 0x0801000804010042ULL, 0x00205e2020202000ULL, nullptr, 54 },
        { 0x0080440200010100ULL, 0x00403e4040404000ULL, nullptr, 54 },
        { 0x2209000245810022ULL, 0x00807e8080808000ULL, nullptr, 53 },
        { 0x4100304000800080ULL, 0x007e010101010100ULL, nullptr, 53 },
        { 0x0030044000200240ULL, 0x007c020202020200ULL, nullptr, 54 },
        { 0x0080408128120200ULL, 0x007a040404040400ULL, nullptr, 54 },
        { 0x0008801000080080ULL, 0x0076080808080800ULL, nullptr, 54 },
        { 0x0002000c10092200ULL, 0x006e101010101000ULL, nullptr, 54 },
        { 0x2044001c80020080ULL, 0x005e202020202000ULL, nullptr, 54 },
        { 0x0029060810018400ULL, 0x003e404040404000ULL, nullptr, 54 },
        { 0x0008472045940200ULL, 0x007e808080808000ULL, nullptr, 53 },
        { 0x00210080011020c1ULL, 0x7e01010101010100ULL, nullptr, 52 },
        { 0x0000814601210012ULL, 0x7c02020202020200ULL, nullptr, 53 },
        { 0x002100c010200149ULL, 0x7a04040404040400ULL, nullptr, 53 },
        { 0x0100082050010045ULL, 0x7608080808080800ULL, nullptr, 53 },
        { 0x410600110820a412ULL, 0x6e10101010101000ULL, nullptr, 53 },
        { 0x0013000204001801ULL, 0x5e20202020202000ULL, nullptr, 53 },
        { 0x044204c810030214ULL, 0x3e40404040404000ULL, nullptr, 53 },
        { 0x0800044120840102ULL, 0x7e80808080808000ULL, nullptr, 52 },
    };
}

namespace
{
    std::unique_ptr<bit_t[]> Attack;
}

//--------------------------------------------------------------------//
//  prototypes
//--------------------------------------------------------------------//

namespace
{
    bit_t attackBishop(const int square, const bit_t all);
    bit_t attackRook  (const int square, const bit_t all);
}

//--------------------------------------------------------------------//
//  functions
//--------------------------------------------------------------------//

void Magic::init()
{
    //  The attack array is dynamically allocated

    int size = 0;
    for (int square = Square::begin(); square < Square::end(); ++square)
    {
        size += 1 << (64 - Bishop[square].shift);
        size += 1 << (64 - Rook  [square].shift);
    }

    Attack.reset(new bit_t[size]);

    //  initialize pointers and attack array
 
    bit_t* ptr = Attack.get(); 

    for (int square = Square::begin(); square < Square::end(); ++square)
    {
        auto& m = Magic::Bishop[square];
        m.ptr   = ptr;
        ptr    += 1 << (64 - m.shift);

        Bit::Enumerator be(m.mask);
        while (be.hasNext())
        {
            const bit_t all = be.getNext();
            const bit_t idx = (all * m.magic) >> m.shift;
            m.ptr[idx]      = attackBishop(square,all);
        }
    }

    for (int square = Square::begin(); square < Square::end(); ++square)
    {
        auto& m = Magic::Rook[square];
        m.ptr   = ptr;
        ptr    += 1 << (64 - m.shift);

        Bit::Enumerator be(m.mask);
        while (be.hasNext())
        {
            const bit_t all = be.getNext();
            const bit_t idx = (all * m.magic) >> m.shift;
            m.ptr[idx]      = attackRook(square,all);
        }
    }
}

namespace
{
    bit_t attackBishop(const int square, const bit_t all)
    {
        const bit_t b = Bit::make(square);
        return Bit::shiftNegative09(Bit::fillNegative09(b,~all)) |
               Bit::shiftNegative07(Bit::fillNegative07(b,~all)) |
               Bit::shiftPositive07(Bit::fillPositive07(b,~all)) |
               Bit::shiftPositive09(Bit::fillPositive09(b,~all));
    }

    bit_t attackRook(const int square, const bit_t all)
    {
        const bit_t b = Bit::make(square);
        return Bit::shiftNegative08(Bit::fillNegative08(b,~all)) |
               Bit::shiftNegative01(Bit::fillNegative01(b,~all)) |
               Bit::shiftPositive01(Bit::fillPositive01(b,~all)) |
               Bit::shiftPositive08(Bit::fillPositive08(b,~all));
    }
}
