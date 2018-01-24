
#ifndef _HUFFMAN_
#define _HUFFMAN_

#include <iostream>

#include<string>
#include<fstream>
#include<unordered_map>
#include<set>
#include<list>
using namespace std;
struct Node
{
    pair<char,int> data;
    Node* left;
    Node* right;
    Node():data(), left(nullptr), right(nullptr) {}
    Node(const pair<char,int>& data, Node* left = nullptr, Node* right = nullptr)
        : data(data), left(left), right(right) {}
};
class Huff
{
    Node* root;
    unordered_map<char,int> frequencyTable;
    unordered_map<char,string> codeTable;
    string inputFile;
    string outputFile;
    string code;
    bool isMemberHelp(Node*const& r, char c) const;
    string binaryCodeHelp(const char c, const Node* start) const;
public:
    Huff():root(nullptr), frequencyTable(), codeTable(), inputFile(""), outputFile(""), code("") {}
    Huff(Node* _root, unordered_map<char,int> _frequencyTable, unordered_map<char,string> _codeTable, string _inputFile, string _outputFile, string _code):root(_root),
        frequencyTable(_frequencyTable),codeTable(_codeTable),inputFile(_inputFile),outputFile(_outputFile), code(_code) {}
    void setInputFile(string name);
    void setOutputFile(string name);
    void createFrequencyTable();
    void createCodeTable();
    void buildTree();
    void printTree() const;
    void printFrequencyTable() const;
    void printCodeTable() const;
    bool isMember( char c) const;
    Node*& findMinNode(list<Node*>& nodes);
    string binaryCode(const char c) const;
    void saveBinaryCode() const;
    void saveDecCode() const;

};
#endif // _HUFFMAN_
