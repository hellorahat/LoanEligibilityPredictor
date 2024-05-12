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

    std::tuple<std::vector<std::string>, std::vector<std::vector<double>>, std::vector<double>> tuple_contents = data_handler.process_data(training_data, categorical_indexes);
    std::vector<std::string> feature_name_vec = std::get<0>(tuple_contents);
    std::vector<std::vector<double>> double_vec = std::get<1>(tuple_contents);
    std::vector<double> impute_vec = std::get<2>(tuple_contents);

    data_handler.vector_to_csv(feature_name_vec, double_vec, "one-hot-encoded-vector");



    // split the data into training and testing vectors

    
    return 0;
}