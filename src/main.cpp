#include "DataHandler/DataHandler.h"
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
    training_vector = data_handler.vector_drop_value(training_vector, 0);

    // get the column index of all categorical values
    std::vector<int> categorical_indexes = data_handler.get_categorical_indexes(training_vector);

    // create a one-hot vector for all of the categorical values
    
    return 0;
}