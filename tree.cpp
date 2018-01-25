#include<tree.h>
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
Node* HuffmanTree::copy(Node* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    return new Node(node->data, copy(node->left), copy(node->right));
}

void HuffmanTree::erase(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    erase(node->left);
    erase(node->right);
    delete node;
}
HuffmanTree::HuffmanTree(const pair<char,int>& data, HuffmanTree left, HuffmanTree right)
{
    root = new Node(data);
    std::swap(root->left, left.root);
    std::swap(root->right, right.root);
}
HuffmanTree& HuffmanTree::operator=(HuffmanTree other)
{
    std::swap(root, other.root);
    return *this;
}
HuffmanTree::~HuffmanTree()
{
    erase(root);
}
bool HuffmanTree::empty()const
{
    return root == nullptr;
}
HuffmanTree HuffmanTree::left() const
{
    return HuffmanTree(root->left);
}

HuffmanTree HuffmanTree::right() const
{
    return HuffmanTree(root->right);
}
void HuffmanTree::prettyPrint(ostream& out, int currentHeight) const
{
    if(empty())
        return;
    right().prettyPrint(out, currentHeight + 1);
    out<<setw(5*currentHeight)<<root->data.first<<root->data.second<<endl;
    left().prettyPrint(out, currentHeight + 1);
}
pair<char,int> HuffmanTree::enterPair(istream& in) const
{
    char c;
    int i;
    cout<<"\n enter symbol: ";
    in>>c;
    cout<<"\n enter symbol frequency: ";
    in>>i;
    return make_pair(c,i);
}
void HuffmanTree::enterHelp(istream& in, Node*& curr)
{
     int answer;
    cout<<"do you want to quit? 0/1 ";
    cin>>answer;
    if(answer == 1)
        return;
    pair<char,int> p = enterPair(in);
    cout<<p.first<<":"<<p.second<<"\n";
    curr = new Node(p);
    cout<<"left -> \n";
    enterHelp(in, curr->left);
    cout<<"right -> \n";
    enterHelp(in, curr->right);
}
void HuffmanTree::enter(istream& in)
{
    enterHelp(in, root);
}
bool HuffmanTree::isMember(const char c) const
{
    if(empty())
        return false;
    if(root->data.first == c)
        return true;
    return left().isMember(c) || right().isMember(c);
}
pair<char, int> HuffmanTree::getRootData() const
{
    return root->data;
}
