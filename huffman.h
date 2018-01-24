#ifndef _HUFFMAN_
#define _HUFFMAN_

#include <iostream>
#include<huffmanTree.cpp>
#include<string>
#include<fstream>
#include<unordered_map>
#include<set>
#include<vector>
using namespace std;
class Huff
{
    BinaryTree tree;
    unordered_map<char,int> table;

    string inputFile;
    string outputFile;


public:
    Huff() {}
    Huff(BinaryTree _tree, unordered_map<char,int> _table, string _inputFile, string _outputFile):tree(_tree),
        table(_table),inputFile(_inputFile),outputFile(_outputFile) {}
    void setInputFile(string name);
    void setOutputFile(string name);
    void createFrequencyTable();
    void buildTree();
    void printTree(ostream& out, int currentHeight) const;
    void printTable() const;
};
#endif // _HUFFMAN_


