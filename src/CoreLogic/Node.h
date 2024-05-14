#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>

/**
 * @file Node.h
 * @brief Header file for the Node class used in decision trees.
 * Contains both declaration and implementation.
*/

using namespace std;

/**
 * @class Node
 * @brief Node class for decision tree nodes.
 * This class represents a node in the decision tree.
*/

class Node{
public:
    Node() : left(nullptr), right(nullptr), feature_index(-1), threshold(0.0), is_leaf(false), label(-1), gini_index(0.0){}

    /// @brief Pointer to the left child node
    unique_ptr<Node> left;

    /// @brief Pointer to the right child node
    unique_ptr<Node> right;

    /// @brief Index of the feature based on which the node splits
    int feature_index;

    /// @brief Threshold value for splitting at this node
    double threshold;

    /// @brief Flag to check if the node is a leaf node
    bool is_leaf;

    /// @brief class label assigned to a leaf node
    int label;

    /// @brief Gini index for the node, used in splitting criteria
    double gini_index;
};

#endif      //NODE_H