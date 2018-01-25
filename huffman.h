
#ifndef _HUFFMAN_
#define _HUFFMAN_

#include <iostream>
#include<tree.h>
#include<string>
#include<fstream>
#include<unordered_map>
#include<set>
#include<list>
using namespace std;
class Huff
{
    HuffmanTree tree;
    unordered_map<char,int> frequencyTable;
    unordered_map<char,string> codeTable;
    string inputFile;
    string outputFile;
    string code;

    void copy(Huff const& other);

    string binaryCodeHelp(const char c, const HuffmanTree& start) const;
    HuffmanTree*& findMinNode(list<HuffmanTree*>& nodes);
    string binaryCode(const char c) const;
public:
    Huff():tree(), frequencyTable(), codeTable(), inputFile(""), outputFile(""), code("") {}
    Huff(HuffmanTree _tree, unordered_map<char,int> _frequencyTable, unordered_map<char,string> _codeTable, string _inputFile, string _outputFile, string _code):tree(_tree),
        frequencyTable(_frequencyTable),codeTable(_codeTable),inputFile(_inputFile),outputFile(_outputFile), code(_code) {}
    Huff& operator=(Huff const& other);
    ~Huff();

    void setInputFile(string name);
    void setOutputFile(string name);

    void createFrequencyTable();
    void createCodeTable();
    void buildTree();

    void printTree() const;
    void printFrequencyTable() const;
    void printCodeTable() const;

    void saveBinaryCode();
    void saveDecCode() const;
    void calculateCompressionRate()const;
};
#endif // _HUFFMAN_
