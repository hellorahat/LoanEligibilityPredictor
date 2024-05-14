//DecisionTree.h
/**
  *@file DecisionTree.h
  *@brief Header file for the DecisionTree class
  *Contain both declaraction and implementation
*/

#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "Node.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <map>

using namespace std;

/**
  *@class DecisionTree
  *@brief Manage the creation and operation of a decision tree.
  *
*This class provides functionality to build and use a decision tree for classification tasks.
*It includes methods for training the tree based on provided data and predicting class labels for new data instances.
*/

class DecisionTree {
public:
  DecisionTree() : root (new Node()) {}                                    //< Constructor initializes the tree with a root node.
  
  void train(vector<vector<double>>& data_vec){                    //< Trains the decision tree using the provided 
    cout << "Training Decision Tree..." <<endl;
    build_tree(root.get(), data_vec, 0, data_vec.size());
  }
int predict(const vector<double>& feature){                              //< predicts the class label for the given features.
  cout<<"Predicting with Decision Trees..." <<endl;
  Node* node = root.get();
  while (!node->is_leaf){
    if(feature[node->feature_index] < node ->threshold){
      node = node->left.get();
    } else {
      node = node->right.get();
    }
  }
  return node->label;
}

private:
  unique_ptr<Node> root;                                          //< Unique pointer to the root node of decision tree
  void build_tree(Node* node, vector<vector<double>>& data_vec, size_t start, size_t end){      //< Recursive function to build the tree.
    if(start >= end) return;

    //determine if this node should be a leaf
    if (should_be_leaf(data_vec, start, end)){
      node -> is_leaf = true;
      node -> label = determine_label(data_vec, start, end);
      return;
    }
    
    //Find the best split
    int best_feature;
    double best_threshold;
    double best_gini = numeric_limits<double>::max();
    for (size_t feature_index = 0; feature_index < data_vec[0].size(); ++ feature_index){
      auto result = find_best_split(data_vec, start, end, feature_index);
      if (result.gini < best_gini){
        best_gini = result.gini;
        best_feature = feature_index;
        best_threshold = result.threshold;
      }
    }

    //set the node's properties
    node -> feature_index = best_feature;
    node -> threshold = best_threshold;
    node -> gini_index = best_gini;

    //recursively build the left and right subtrees
    node->left.reset(new Node());
    node->right.reset(new Node());
    size_t split_index = partition_data (data_vec, start, end, best_feature, best_threshold);
    build_tree(node->left.get(), data_vec, start, split_index);
    build_tree(node->right.get(), data_vec, split_index, end);
  }

  bool should_be_leaf(const vector<vector<double>>& data_vec, size_t start, size_t end){            //< Determine if the current node should be a leaf.
    //Example stopping condition: if all data points have the same label
    int first_label = data_vec[start].back();
    for (size_t i = start + 1; i < end; ++i){
      if (data_vec[i].back() != first_label){
        return false;
      }
    }
  return true;
  }

  int determine_label(const vector<vector<double>>& data_vec, size_t start, size_t end){         //< Determine the label of the leaf node based on majority voting.
    //Majority voting for label
    map<int, int> label_counts;
    for (size_t i = start; i < end; ++i){
      int label = data_vec[i].back();
      label_counts[label]++;
    }
    int majority_label = -1;
    int max_count = 0;
    for(auto& pair : label_counts){
      if (pair.second > max_count){
        max_count = pair.second;
        majority_label = pair.first;
      }
    }
    return majority_label;
  }

struct SplitResult {
  double gini;                  //< Gini index of the split.
  double threshold;             //< Threshold value of the split.
};

SplitResult find_best_split(const vector<vector<double>>& data_vec, size_t start, size_t end, size_t feature_index){              //< Finds the best split based on Gini index.
  vector<double> values;
  for (size_t i = start; i < end; ++i){
    values.push_back(data_vec[i][feature_index]);
  }
  sort(values.begin(), values.end());

  double best_gini = numeric_limits<double>::max();
  double best_threshold = 0;

  for (size_t i = 1; i < values.size(); ++i){
    double threshold = (values[i - 1] + values[i])/2;
    double gini = calculate_gini_index(data_vec, start, end, feature_index, threshold);
    if (gini < best_gini){
      best_gini = gini;
      best_threshold = threshold;
    }
  }

  return {best_gini, best_threshold};
}

size_t partition_data (vector<vector<double>>& data_vec, size_t start, size_t end, int feature_index, double threshold){    //< Partitions the data into left and right based on the threshold.
  size_t mid = start;
  for (size_t i = start; i < end; ++i){
    if(data_vec[i][feature_index] < threshold){
      swap (data_vec[mid], data_vec[i]);
      mid++;
    }
  }
  return mid;
}

double calculate_gini_index(const vector<vector<double>>& data_vec, size_t start, size_t end, size_t feature_index, double threshold){     //< Calculates the Gini index for a given split.
  map<int,int> left_counts, right_counts;
  int left_size = 0, right_size = 0;

  for (size_t i = start; i < end; ++i){
    int label = data_vec[i].back();
    if (data_vec[i][feature_index] < threshold){
      left_counts[label]++;
      left_size++;
  } else {
    right_counts[label]++;
    right_size++;
  }
}

double left_gini = 1.0, right_gini = 1.0;
for (auto& pair : left_counts){
  double p = pair.second/(double)left_size;
  left_gini -= p * p;
}

//weighted average of the Gini index
return (left_gini* left_size + right_gini * right_size) / (left_size + right_size);
}

private:
  unique_ptr<Node> root;                                                                    //unique pointer to the root node of the decision tree
  void build_tree(Node*& node, const vector<vector<double>>& data_vec, size_t start, size_t end);  //recursive function to build the tree
};

#endif  //DECISIONTREE_H
