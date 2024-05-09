//DecisionTree.h

#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "Node.h"
#include <vector>

class DTree{
public:
  void train(const vector<vector<double>>& features, const vector <int>& labels);
  int predict(const vector<double>& feature);

private:
  Node* root;
  void build_tree(Node*& node, const vector<vector<double>>& features, const vector<int>& labels);
};
