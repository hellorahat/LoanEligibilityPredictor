// RandomForest.h

#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H

include "DecisionTree.h"
include <vector>

using namespace std;

class randomForest {
public:
  randomForest(int num_trees);
  void train (const vector<vector<double>>& features, const vector<int>& labels);
  int predict(const vector<double>& feature);

private:
  int num_trees_;
  vector<DecisionTree> trees_;
}

#endif
