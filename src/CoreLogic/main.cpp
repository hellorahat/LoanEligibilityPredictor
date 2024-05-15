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
    
    //perform k-fold cross validation
    int k = 2;
    double average_accuracy = forest.kFoldCrossValidation(data, k);
    std::cout << "Average Cross Validation Accuracy: " << average_accuracy * 100 <<"%" << std::endl;
    
    //optionally, evaluate the model if you have a separate test set
    RandomForest::AccuracyMetrics metrics = forest.evaluate_accuracy(data);
    std::cout<<"Model Accuracy: "<< metrics.accuracy <<"%" << std::endl;
    std::cout<<"True Positive: " << metrics.true_positives <<std::endl;
    std::cout << "True Negatives: " << metrics.true_negatives << std::endl;
    std::cout << "False Positives: " << metrics.false_positives << std::endl;
    std::cout << "False Negatives: " << metrics.false_negatives << std::endl;

    delete df; //Clean up DataFrame object
    return 0;
}