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
    cout<<"\nsymbol: ";
    in>>c;
    if(c == '*')
        c = ' ';
    cout<<"\nsymbol frequency: ";
    in>>i;
    return make_pair(c,i);
}
void HuffmanTree::enterHelp(istream& in, Node*& curr)
{
    int answer;
    cout<<"stop 0/1 ";
    cin>>answer;
    if(answer == 1)
        return;
    pair<char,int> p = enterPair(in);
    cout<<p.first<<":"<<p.second<<"\n";
    curr = new Node(p);
    cout<<"\nleft of "<<curr->data.first<<curr->data.second<<" -> \n";
    enterHelp(in, curr->left);
    cout<<"\nright of "<<curr->data.first<<curr->data.second<<" -> \n";
    enterHelp(in, curr->right);
}
void HuffmanTree::enter(istream& in)
{
    cout<<"for nodes without symbols, set * as their symbol\n";
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

void HuffmanTree::save(string fname) const
{
    ofstream fout;
    fout.open(fname, ios::out);//изтрива всичко друго, което е имало преди във файла
    prettyPrint(fout,0);
    fout.close();
}
