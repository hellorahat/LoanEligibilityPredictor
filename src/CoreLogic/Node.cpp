#include <iostream>
#include <vector>
#include <memory>

using namespace std;

//create the class for the nodes.
class Node{
public:
    Node():left(nullptr), right(nullptr), feature_index(-1), threshold(0.0), is_leaf(false), label(-1), gini_index(0){}    // Constructor for the nodes.

    unique_ptr<Node> left;
    unique_ptr<Node> right;
    int feature_index;
    double threshold;
    bool is_leaf;
    int label;
    int gini_index;
}
