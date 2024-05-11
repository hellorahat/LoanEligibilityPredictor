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

    // push all categorical column indexes into a vector
    std::vector<int> categorical_indexes;
    categorical_indexes.push_back(1); // column 1 is categorical

    // for all categorical indexes, convert it into one hot encoding
    for(int index : categorical_indexes) {
        std::vector<std::vector<std::string>> one_hot_vec = data_handler.one_hot_encoding(training_vector, index);
        // drop the column as we will be inputting the one_hot_vec in its place
        training_vector = data_handler.vector_drop_column(training_vector, index);
        // resize to accomodate memory for the additional columns, then insert the one-hot encoding into the index
        for(int row = 0; row < one_hot_vec.size(); row++) {
            // Resize the row of training_vector to accommodate one_hot_vec
            training_vector[row].resize(one_hot_vec[row].size());

            // Insert the one-hot encoded data into the specified index
            auto it = training_vector[row].begin() + index;
            training_vector[row].insert(it, one_hot_vec[row].begin(), one_hot_vec[row].end());
            // training_vector.insert(training_vector.begin() + index, one_hot_vec.begin(), one_hot_vec.end());
        }
    }
    data_handler.vector_to_csv(training_vector, "one-hot-encoding");
    
    // split the data into training and testing vectors
    
    return 0;
}