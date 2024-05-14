#include "DataProcessing/DataHandler.h"
#include "Includes/DataFrame.h"
#include "CoreLogic/SuggestionGenerator.h"
#include "CoreLogic/RandomForest.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    std::ifstream training_data(argv[1]);
    DataHandler data_handler;
    std::vector<int> categorical_indexes;
    // push all categorical columns onto the vector
    categorical_indexes.push_back(0); 
    categorical_indexes.push_back(1);

    // call data processor
    DataFrame *df = data_handler.process_data(training_data, categorical_indexes);
    // place the information obtained from the function into variables
    std::vector<std::string> feature_name_vec = df->get_feature_name_vec(); 
    std::vector<std::vector<double>> double_vec = df->get_data_vec(); 
    std::vector<double> impute_vec = df->get_impute_vec();
    std::vector<double> test_point = {0,1,0,0,0,0,0,0,1,0.1001,84.12,10.2036,10,450,2230.04,5630,23,1,0,0,0};

    RandomForest *rf = new RandomForest(2);
    rf->train(double_vec);
    std::cout<<"Prediction:"<<rf->predict(test_point)<<std::endl;

}