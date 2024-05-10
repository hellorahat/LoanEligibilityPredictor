#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>

class Node{
public:
  Node(): left(nullptr), right(nullptr), feature_index(-1), threshold(0.0), is_leaf(false), label(-1), gini_index(0){}

  unique_ptr<Node> left; 
  unique_ptr<Node> right;
  int feature_index;
  double threshold
  bool is_leaf;
  int label;
  int gini_index;

#endif
