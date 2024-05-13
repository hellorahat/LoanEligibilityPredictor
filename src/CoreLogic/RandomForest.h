/**
  *@file RandomForest.h
  *@brief Header file the RandomForest class.
  *Contain both declaration and implementation.
  */

#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H

#include "DecisionTree.h"
#include <vector>
#include <cstdlib>

using namespace std;

/**
  *@class RandomForest
  *@brief Manage the creation and operation of a random forest.
  *
  *This class encapsulates a collection of decision trees to form a random forest.
  *It provides methods to train the forest using bagging and to predict class labels using majority voting among the tree.
  */

class RandomForest{
public:
  /**
    *@brief Constructor that initializes the forest with a specified number of trees.
    *@param num_trees Number of trees to include in the forest.
    */
  RandomForest(int num_trees): num_trees_(num_trees), trees_(num_trees){}          //Constructor initializes the forest with a specified number of trees
  /**
    *@brief Trains the random forest using the provided dataset.
    *@param data_vec Data used for training the random forest. Each tree is train on a bootstrap sample of this data.
    */
  void train (const vector<vector<double>>& data_vec){
    cout <<"Training "<<num_trees_ << " trees with bagging..." << endl;
    int num_samples = data_vec.size();
    for (auto& tree : trees_){
      vector<vector<double>> sample_data_vec;
      for (size_t i = 0; i < num_samples; ++i){
      size_t idx = rand() % num_samples;
      sample_data_vec.push_back(data_vec[idx]);
    }
    tree.train(sample_data_vec);
  }
}
/**
  *@brief Predict the class label for the given feature using majority voting among all trees.
  *@param feature Vcetor of feature for which the class label is predicted.
  *@return The predicted class label, determined by majority vote.
  */

int predict(const vector<double>& feature){
  vector<int> votes(num_trees_,0);
  for (auto& tree : trees_){
    int prediction = tree.predict(feature);
    votes[prediction]++;
  }
return distance(votes.begin(), max_element(votes.begin(), votes.end()));        //return the class with the most votes
}

private:
  int num_trees_;                                                  //Number of trees in the forest
  vector<DecisionTree> trees_;                                     //Vector of decision trees
}

#endif  //RANDOMFOREST_H
