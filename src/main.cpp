#include "DataProcessing/DataHandler.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    std::ifstream training_data(argv[1]);
    DataHandler data_handler;
    std::vector<std::vector<std::string>> training_vector;

    // csv to vector
    training_vector = data_handler.csv_to_vector(training_data);
    training_data.close();

    // attempt to get the column index of all categorical values
    // std::vector<int> categorical_indexes = data_handler.get_categorical_indexes(training_vector);
    std::vector<int> categorical_indexes;
    categorical_indexes.push_back(1); // column 1 is categorical

    // data_handler.vector_to_csv(training_vector, "csvData");

    // fill in NULL values
    // training_vector = data_handler.impute_data(training_vector, categorical_indexes);

    // clean the dataset
    // training_vector = data_handler.clean_vector_data(training_vector);


    // create a one-hot vector for all of the categorical values
    std::vector<std::vector<std::string>> one_hot_vec = data_handler.one_hot_vector(training_vector, categorical_indexes);

    // split the data into training and testing vectors
    
    return 0;
}