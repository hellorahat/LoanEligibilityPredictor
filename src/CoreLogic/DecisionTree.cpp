#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Build the class for the decision tree called DTree.
class DTree{
public:
  DTree(): root(new Node()) {}
  void train (const vector<vector<double>> data_vec){
      cout << "Training Decision Tree..." <<endl;
        //training logic
      for (size_t row=0; row < data_vec.size(); row++) {
        for (size_t col=0; col < data_vec[row].size(); col++){
          double current_iteration = data_vec[row][col];
          //use current_iteration for training logic
        }
      }
  }
  int predict (const vector<double>& feature){
    cout <<"Predict with Decision Tree..." <<endl;
    return 0;    //placeholder return
  }
private:
  unique_ptr<Node> root;
  void build_tree<Node*& node, const (vector<vector<double>> data_vec, size_t start, size_t end);
};
