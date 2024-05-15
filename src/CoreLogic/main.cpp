#include <iostream>
#include <fstream>
#include "RandomForest.h"
#include "..\DataProcessing\DataHandler.h"

int main(){
    DataHandler data_handler;
    std::vector<int> categorical_indexes = {0, 1};        //adjust based on your dataset
    std::string filename = "C:\\Users\\qasda\\OneDrive\\文档\\GitHub\\LoanRepaymentPredictor\\data\\loan_data.csv";                          //Update this path

    std::cout<< "Attempting to open file at: " << filename <<std:: endl;
    std::ifstream file(filename);
    if(!file){
        std::cerr<< "Error opening file!" << std::endl;
        return 1;
    }

    //Process the data
    DataFrame *df = data_handler.process_data (file, categorical_indexes);
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
    file.close();
    return 0;
}