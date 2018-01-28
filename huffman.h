
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

//по-удачно има - Compressor
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
    Huff(Huff const& other);
    Huff& operator=(Huff const& other);

    void setInputFile(string name);
    void setOutputFile(string name);

    string getInputFileName() const;
    string getOutputFileName() const;
    string getCode() const;

    void createFrequencyTable();
    void createCodeTable();
    void buildTree();
    void enterTree();
    void createBinaryCode();
    void calculateCompressionRate();

    void printTree() const;
    void printFrequencyTable() const;
    void printCodeTable() const;


    void saveBinaryCode() const;
    void saveDecCode() const;
    void saveTree() const;

    void run();
};
#endif // _HUFFMAN_
