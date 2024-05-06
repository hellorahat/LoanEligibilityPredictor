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

    //drop the 0th column, since the id is not necessary
    training_vector = data_handler.vector_drop_column(training_vector, 0);

    // attempt to get the column index of all categorical values
    std::vector<int> categorical_indexes = data_handler.get_categorical_indexes(training_vector);
    categorical_indexes.push_back(9); // credit_history is categorical even though the value is either 0 or 1

    // fill in NULL values
    training_vector = data_handler.impute_data(training_vector, categorical_indexes);

    // clean the dataset
    training_vector = data_handler.clean_vector_data(training_vector);

    // create a one-hot vector for all of the categorical values
    std::vector<std::vector<std::string>> one_hot_vec = data_handler.one_hot_vector(training_vector, categorical_indexes);

    // print the data
    data_handler.print_vector_data(one_hot_vec);

    return 0;
}