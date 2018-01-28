#ifndef _DECOMPRESSOR_H_
#define _DECOMPRESSOR_H_

#include<tree.h>
#include<iostream>
#include<string>
using namespace std;
class Decompressor
{
    HuffmanTree tree;
    string inputFile;
    string outputFile;

public:
    Decompressor():tree(), inputFile(""),outputFile(""){}
    Decompressor(HuffmanTree _tree, string _ifile, string _ofile):tree(_tree), inputFile(_ifile), outputFile(_ofile){}
    Decompressor& operator=(Decompressor const& other);

    string getInputFile()const;
    string getOutputFile() const;

    void setInputFile(string name);
    void setOutputFile(string name);

    void enterTree();
    string readCode() const;
    void decompress(string& code, HuffmanTree::Position curr,string& res);
    void run();
};

#endif // _DECOMPRESSOR_H_
