#include "DataProcessing/DataHandler.h"
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
    std::tuple<std::vector<std::string>, std::vector<std::vector<double>>, std::vector<double>> tuple_contents = data_handler.process_data(training_data, categorical_indexes);
    // place the information obtained from the function into variables
    std::vector<std::string> feature_name_vec = std::get<0>(tuple_contents); // the header row: this contains the column names
    std::vector<std::vector<double>> double_vec = std::get<1>(tuple_contents); // the raw data content
    std::vector<double> impute_vec = std::get<2>(tuple_contents); // a vector that will be used to replace missing values with, uses mean for numerical, and mode for categorical.

    data_handler.vector_to_csv(feature_name_vec, double_vec, "one-hot-encoded-vector");

    // split the data into training and testing vectors

    
    return 0;
}