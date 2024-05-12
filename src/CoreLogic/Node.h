//Node.h
/**
  *@file Node.h
  *@brief Header file for the Node class used in decision trees.
  *Contains both declaration and implementation.
  */

#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>

//**
  *@class Node
  *@brief Node class for decision tree nodes.
  *This class represents a node in the decision tree.
  */
class Node{
public:
  Node(): left(nullptr), right(nullptr), feature_index(-1), threshold(0.0), is_leaf(false), label(-1), gini_index(0){}

  unique_ptr<Node> left;                               //pointer to the left child node
  unique_ptr<Node> right;                              //pointer to the right child node
  int feature_index;                                   //Index of feature based on which the node splits
  double threshold                                     //Threshold value for splitting at this node
  bool is_leaf;                                        //Flag to check if the node is a leaf node
  int label;                                          //Class label assigned to a leaf node
  int gini_index;                                      // Gini index for the node, used in splitting criteria

#endif      //NODE_H
