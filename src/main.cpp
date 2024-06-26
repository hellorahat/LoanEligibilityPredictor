#include "DataProcessing/DataHandler.h"
#include "Includes/DataFrame.h"
#include "CoreLogic/SuggestionGenerator.h"
#include "CoreLogic/RandomForest.h"
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
    
    // closest vector: {0,1,0,1,0,0,0,0,0,0.1103,327.53,10.7389,13.04,702,8159.96,5394,53.4,1,0,0,0};
    std::vector<double> negative_point = double_vec[90];
    
    // SuggestionGenerator sg = SuggestionGenerator();
    // std::vector<double> closest_positive_point = sg.get_closest_positive_prediction(negative_point, df);

    // std::vector<std::vector<double>> merged_vec;
    // merged_vec.push_back(negative_point);
    // merged_vec.push_back(closest_positive_point);

    // data_handler.vector_to_csv(df->get_feature_name_vec(), merged_vec, "closest-point");
    
    RandomForest *rf = new RandomForest(3);
    rf->train(double_vec);
    // std::vector<double> test_point = {0,1,0,0,0,0,0,0,1,0.1347,360.43,10.4341,22.09,677,6713.04,13846,71,2,0,1};
    // rf->predict(test_point);

    return 0;
}