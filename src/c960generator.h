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

#ifndef C960GENERATOR_H
#define C960GENERATOR_H

#include <string>
#include <vector>

class C960Generator
{
private:
    enum class Pieces {
        rook, knight, bishop, queen, king
    };
    enum class Columns {
        A, B, C, D, E ,F, G, H
    };
    std::vector<std::vector<Pieces>> m_krn_positions;
    std::string m_pieces;
    std::string m_result;
public:
    C960Generator(std::string pieces = "RNBQK");
    std::string getPosition(int id = 518);
    void setStringOfPieces(std::string pieces);
};

#endif //C960GENERATOR_H
