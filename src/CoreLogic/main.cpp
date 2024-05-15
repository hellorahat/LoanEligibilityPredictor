#include <iostream>
#include <fstream>
#include "RandomForest.h"
#include "..\DataProcessing\DataHandler.h"
#include "..\includes\DataFrame.h"


int main(int argc, char* argv[]) {
    DataHandler data_handler;
    std::vector<int> categorical_indexes = {0, 1};        //adjust based on your data

    std::ifstream training_data(argv[1]);

    //Process the data
    DataFrame *df = data_handler.process_data (training_data, categorical_indexes);
    std::vector<std::vector<double>> data = df -> get_data_vec();

    //initialize RandomForest
    int num_trees = 3;         //Number of trees in the forest.
    RandomForest forest(num_trees);

    //Train the RandomForest
    forest.train(data);

    //optionally, evaluate the model if you have a separate test set
    double accuracy = forest.evaluate(data);        //here, using the same data for simplicity
    std:: cout<< "Model Accuracy: " << accuracy * 100 << "%" << std:: endl;

    delete df; //Clean up DataFrame object
    return 0;
}