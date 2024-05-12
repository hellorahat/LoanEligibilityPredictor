#include "DataProcessing/DataHandler.h"
#include "DataProcessing/DataFrame.h"
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
    std::vector<std::string> feature_name_vec = df->get_feature_name_vec(); // the header row: this contains the column names
    std::vector<std::vector<double>> double_vec = df->get_data_vec(); // the raw data content
    std::vector<double> impute_vec = df->get_impute_vec(); // a vector that will be used to replace missing values with, uses mean for numerical, and mode for categorical.
    /*
    The following variable is an unordered_map where "ColumnName" is mapped to another unordered_map where "CategoryName" is mapped to the column index in the raw data vector.
        e.g:  - categorical_group["ColumnName1"] = ["category1"]:0, ["category2"]:1, ["category3"]:2
              - categorical_group["ColumnName2"] = ["category4"]:5, ["category5"]:6, ["category6"]:7
              - categorical_group["purpose"]["debt_consolidation"] = COLUMN_INDEX (int)
    */
    std::unordered_map<std::string, std::unordered_map<std::string, int>> categorical_groups = df->get_categorical_groups();

    data_handler.vector_to_csv(feature_name_vec, double_vec, "one-hot-encoded-vector");



    
    return 0;
}