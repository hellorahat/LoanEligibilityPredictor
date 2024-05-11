#infdef DECISIONTREE_H
#define DECISIONTREE_H

#include "Node.h"
#include <iostream>
#include <vector>

class DecisionTree {
public:
  DecisionTree() : root (new Node()){}                                    //Constructor initializes the tree with a root node
  void train(const vector<vector<double>>& data_vec){
    cout << "Training Decision Tree..." <<endl;
    for (size_t row = 0; row < data_vec.size(); row++){
      for (size_t col=0; col < data_vec[row].size(); col++){
        double current_iteration = data_vec[row][col];
      }
    }
  }
int predict(const vector<double>& feature){
  cout<<"Predicting with Decision Trees..." <<endl;
  return 0;                                                        //placeholder return
}
private:
  unique_ptr<Node> root;                                          //Unique pointer to the root node of decision tree
  void build_tree(Node*& node, const vector<vector<double>>& data_vec, size_t start, size_t end);                      //Recursive function to build the tree
};

#endif
