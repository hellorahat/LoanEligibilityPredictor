#include <iostream>
#include <algorithm>
#include "DecisionTree.h"

using namespace std;

void DTree::train(const vector<vector<double>>& features, const vector<int>& labels) {
  cout << "Training Decision Tree..." <<endl;
  for (size_t row =1; row < feature.size(); row++){
    for (size_t col = 0; col < feature[row].size(); col++){
      double current_iteration = feature[row][col];
    }
  }
}

int DTree::predict (const vector<double>&feature) {
  cout<< "Predicting with decision tree..." <<endl;
  return 0;
}
