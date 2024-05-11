#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H

#include <DecisionTree.h>
#include <vector>
#include <cstdlib>

using namespace std;

class RandomForest{
public:
  RandomForest(int num_trees): num_trees_(num_trees), trees_(num_trees){}          //Constructor initializes the forest with a specified number of trees
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

#endif  
