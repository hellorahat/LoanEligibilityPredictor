//RandomForest.cpp

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class randomForest{
public:
  randomForest (int num_trees) : num_trees_(num_trees), tree_(num_trees) {}
  void train (const vector<vector<double>> data_vec){
      cout <<"Training " << num_trees_ << "trees  with bagging... " << endl;
      int num_samples = data_vec.size();
      for (auto& tree:trees_){
          vector<vector<double>> sample_data_vec;
          for (size_t i = 0; i < num_samples; i++){
              size_t idx = rand() % num_samples;
              sample_data_vec.push_back(data_vec[idx]);
          }
      tree.train(sample_data_vec);
      }
  }
int predict (const vector <double>& feature){
    vector<int> vote(num_trees_, 0);
    for (auto& tree:trees_){
        int prediction = tree.predict(feature);
        vote[prediction] ++;
    }
return distance (votes.begin(), max_element(votes.begin(), votes.end()));
}

private:
  int num_trees_;
  vector <DTree> trees_;
};

