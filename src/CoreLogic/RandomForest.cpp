//RandomForest.cpp

#include <iostream>
#include <cstdlib>
#include "RandomForest.h"

using namespace std;

RandomForest::RandomForest(int num_trees) : num_trees_(num_trees), trees_(num_trees){}

void RandomForest::train(const vector <vector<double>>& features, const vector<int>& labels) {
  cout << "Training " << num_trees_ << " trees with bagging... " <<endl;
  int num_samples = features.size();
  for (auto& tree : trees_) {
    vector<vector<double>> sample_features;
    vector<int> sample_labels;
    for (size_t i = 0; i < num_samples; ++i){
      size_t idx=rand() % num_samples;
      sample_features.push_back (features[idx]);
      sample_labels.push_back (labels[idx]);
    }
  tree.train(sample_features, sample_labels);
  }
}

int RandomForest::predict(const vector<double>& feature){
    vector<int> votes (num_trees_, 0);
    for (auto& tree:trees_){
      int prediction = tree.predict(feature);
      vote[prediction]++;
    }
return distance(vote.begin(), max_element(votes.begin(), vote.end()));
}

