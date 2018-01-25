
#ifndef _TREE_HUFFMAN_H_
#define _TREE_HUFFMAN_H_
#include<iostream>
#include<iomanip>
#include<fstream>
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
class HuffmanTree
{
    Node* root;
    Node* copy(Node* node);
    void erase(Node* node);
    HuffmanTree(Node* root): root(copy(root)) {}
    void enterHelp(istream& in , Node*& curr);
    pair<char,int> enterPair(istream& in) const;
public:
    HuffmanTree(): root(nullptr) {}

    HuffmanTree(const pair<char,int>& data, HuffmanTree left, HuffmanTree right);

    HuffmanTree(HuffmanTree&& other) noexcept: HuffmanTree()
    {
        std::swap(root, other.root);
    }

    HuffmanTree(HuffmanTree const& other): root(copy(other.root)) {}

    HuffmanTree& operator=(HuffmanTree other);

    ~HuffmanTree();
    bool empty()const;

    HuffmanTree left() const;

    HuffmanTree right() const;

    void prettyPrint(ostream& out = cout,int currentHeight = 0) const;
    void enter(istream& in);
    bool isMember(const char c) const;
    pair<char, int> getRootData() const;
};

#endif // _TREE_HUFFMAN_H_
