/*
MIT License

Copyright (c) 2017 José Puga

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "c960generator.h"

#include <cstdlib>

using namespace std;


C960Generator::C960Generator(string pieces){
    m_pieces = pieces;
    m_result.resize(8, ' ');
    m_krn_positions.reserve(10);
    m_krn_positions.insert(m_krn_positions.begin(),{
        { Pieces::knight, Pieces::knight, Pieces::rook, Pieces::king, Pieces::rook }, //0
        { Pieces::knight, Pieces::rook, Pieces::knight, Pieces::king, Pieces::rook }, //1
        { Pieces::knight, Pieces::rook, Pieces::king, Pieces::knight, Pieces::rook }, //2
        { Pieces::knight, Pieces::rook, Pieces::king, Pieces::rook, Pieces::knight }, //3
        { Pieces::rook, Pieces::knight, Pieces::knight, Pieces::king, Pieces::rook }, //4
        { Pieces::rook, Pieces::knight, Pieces::king, Pieces::knight, Pieces::rook }, //5
        { Pieces::rook, Pieces::knight, Pieces::king, Pieces::rook, Pieces::knight }, //6
        { Pieces::rook, Pieces::king, Pieces::knight, Pieces::knight, Pieces::rook }, //7
        { Pieces::rook, Pieces::king, Pieces::knight, Pieces::rook, Pieces::knight }, //8
        { Pieces::rook, Pieces::king, Pieces::rook, Pieces::knight, Pieces::knight }  //9
    });
}

void C960Generator::setStringOfPieces(string pieces){
    m_pieces = pieces;
    return;
}

string C960Generator::getPosition(int id){
    div_t tmp_div;
    int krn_code;
    Columns tmp_col;
    int spaces_count = 0;

    m_result = "";
    m_result.resize(8, ' ');

    //(1) LIGHT-SQUARE BISHOP
    //=======================
    //Divide the id by 4, producing a truncated integer and a remainder. The remainder locates
    //the light-square Bishop: 0 means col B, 1 means col D, 2 means col F, and 3 means col H.
    tmp_div = div(id,4);
    switch (tmp_div.rem) {
    case 0:
        tmp_col = Columns::B;
        break;
    case 1:
        tmp_col = Columns::D;
        break;
    case 2:
        tmp_col = Columns::F;
        break;
    case 3:
        tmp_col = Columns::H;
        break;
    }
    m_result.at(static_cast<int>(tmp_col)) = m_pieces.at(static_cast<int>(Pieces::bishop));

    //(2) DARK-SQUARE BISHOP
    //======================
    //Take the previous truncated integer and divide by 4, producing another integer and a remainder.
    //This remainder locates the dark-square Bishop: 0 means col A, 1 means col C, 2 means col E, and 3 col G.
    tmp_div = div(tmp_div.quot,4);
    switch (tmp_div.rem) {
    case 0:
        tmp_col = Columns::A;
        break;
    case 1:
        tmp_col = Columns::C;
        break;
    case 2:
        tmp_col = Columns::E;
        break;
    case 3:
        tmp_col = Columns::G;
        break;
    }
    m_result.at(static_cast<int>(tmp_col)) = m_pieces.at(static_cast<int>(Pieces::bishop));

    //(3) QUEEN
    //=========
    //Take the previous truncated integer and divide by 6, producing another integer and a remainder. This remainder
    //locates the queen, and identifies the number of the vacant square it occupies (counting from the left, where 0
    //is the leftmost square and 5 is the rightmost square).
    tmp_div = div(tmp_div.quot,6);
    spaces_count = 0;
    for (unsigned int i = 0; i < m_result.length(); i++) {
        if (m_result.at(i) == ' ') {
            if (spaces_count == tmp_div.rem) {
                m_result.at(i) = m_pieces.at(static_cast<int>(Pieces::queen));
                break;
            }
            spaces_count++;
        }
    }

    //(4) KING, ROOKS & KNIGHTS
    //=========================
    //The previous truncated integer now has a value from 0 to 9 inclusive. Its value, called the KRN code
    //(pronounced "kern"),indicates the positions of the king, rooks, and knights among the remaining 5 squares.
    krn_code = tmp_div.quot;
    spaces_count = 0;
    for (unsigned int i = 0; i < m_result.length(); i++) {
        if (m_result.at(i) == ' ') {
            m_result.at(i) = m_pieces.at(static_cast<int>(m_krn_positions[krn_code][spaces_count]));
            spaces_count++;
        }
     }

    return m_result;
}
