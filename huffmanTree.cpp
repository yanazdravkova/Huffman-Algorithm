#ifndef _HUFFMAN_TREE_
#define _HUFFMAN_TREE_

#include<iostream>
#include<iomanip>
using namespace std;
class BinaryTree {
  struct Node {
    pair<char,int> data;
    Node* left;
    Node* right;

    Node(const pair<char,int>& data, Node* left = nullptr, Node* right = nullptr)
      : data(data), left(left), right(right) {}
  };

  Node* root;

  Node* copy(Node* node) {
    if (node == nullptr) {
      return nullptr;
    }

    return new Node(node->data, copy(node->left), copy(node->right));
  }

  void erase(Node* node) {
    if (node == nullptr) {
      return;
    }

    erase(node->left);
    erase(node->right);
    delete node;
  }
  bool isLeaf(Node* node)
  {
      return node->left == nullptr && node->right == nullptr;
  }
  BinaryTree(Node* root): root(copy(root)) {}

public:

  class Position {
    Node*& p;

  public:
     Position(Node*& p): p(p) {};
     int getValue() const
     {
         return p->data.first;
     }
     char getChar() const
     {
         return p->data.second;
     }
    operator bool() const {
      return p != nullptr;
    }

    bool operator!() {
      return !(bool)*this;
    }


    Position left() const {
      return Position(p->left);
    }

    Position right() const {
      return Position(p->right);
    }
  };

  BinaryTree(): root(nullptr) {}

  BinaryTree(const pair<char, int>& data, BinaryTree left, BinaryTree right) {
    root = new Node(data);
    std::swap(root->left, left.root);
    std::swap(root->right, right.root);
  }

  BinaryTree(BinaryTree&& other) noexcept: BinaryTree() {
    std::swap(root, other.root);
  }

  BinaryTree(BinaryTree const& other): root(copy(other.root)) {}

  BinaryTree& operator=(BinaryTree other) {
    std::swap(root, other.root);
    return *this;
  }

  ~BinaryTree() {
    erase(root);
  }

  Position getRoot() {
    return Position(root);
  }

  BinaryTree left() const {
    return BinaryTree(root->left);
  }

  BinaryTree right() const {
    return BinaryTree(root->right);
  }

  bool empty() const {
    return root == nullptr;
  }

void prettyPrint(std::ostream& out, int currentHeight) const
{
    {
    if(empty())
        return;
    right().prettyPrint(out, currentHeight + 1);
    if(root->data.first == ' ')
        out<<setw(5*currentHeight)<<" "<<root->data.second<<endl;
    else
        out<<setw(5*currentHeight)<<" "<<root->data.first<<" "<<root->data.second<<endl;
    left().prettyPrint(out, currentHeight + 1);
}
}
};
#endif // _HUFFMAN_TREE_
