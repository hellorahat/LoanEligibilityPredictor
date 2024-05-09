// Node.h
/**
  *@file Node.h
  *@brief Node class for decision tree nodes.
*/

#ifndef NODE_H
#define NODE_H

class Node{
public:
  Node() : left (nullptr), right(nullptr), feature_index(-1), threshold(0.0), is_leaf(false), label(-1){}
  Node* left;
  Node* right;
  int feature_index;
  double threshold;
  bool is_leaf;
  int lable;
};

#endif  //NODE_H
