/**
 * @file DataFrame.h
 * @author Rohan
 * @brief A header that contains the dataframe class for the application. The DataFrame class provides easy access to the feature name, data, and impute vectors.
 * @version 0.1
 * @date 2024-05-12
 */

// Create header guard
#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <iostream>
#include <unordered_map>
#include <vector>

class DataFrame {
public:
    DataFrame(std::vector<std::string> feature_names, std::vector<std::vector<double>> data, std::vector<double> impute_vals, std::unordered_map<std::string, std::unordered_map<std::string, int>> categories) {
        feature_name_vec = feature_names;
        data_vec = data;
        impute_vec = impute_vals;
        categorical_groups = categories;
    }
    std::vector<std::string> get_feature_name_vec() { return feature_name_vec; }
    std::vector<std::vector<double>> get_data_vec() { return data_vec; }
    std::vector<double> get_impute_vec() { return impute_vec; }

    /*
    The following variable is an unordered_map where "ColumnName" is mapped to another unordered_map where "CategoryName" is mapped to the column index in the raw data vector.
        e.g:  - categorical_group["ColumnName1"] = ["category1"]:0, ["category2"]:1, ["category3"]:2
              - categorical_group["ColumnName2"] = ["category4"]:5, ["category5"]:6, ["category6"]:7
              - categorical_group["purpose"]["debt_consolidation"] = COLUMN_INDEX (int)
    */
    std::unordered_map<std::string, std::unordered_map<std::string, int>> get_categorical_groups() { return categorical_groups; }

    int get_col_index_from_feature_name(std::string feature_name) {
        for(int col = 0; col < this->feature_name_vec.size(); col++) {
            if(this->feature_name_vec[col] == feature_name) return col;
        }
        return -1;
    }

    std::string get_feature_name_from_col_index(int index) { return feature_name_vec[index]; }
    
    std::unordered_map<std::string, int> get_categories_in_column(std::string col_name) { return this->categorical_groups[col_name]; }
    int get_column_index_of_category(std::string col_name, std::string category_name) { return this->categorical_groups[col_name][category_name]; }

private:
    std::vector<std::string> feature_name_vec;
    std::vector<std::vector<double>> data_vec;
    std::vector<double> impute_vec;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> categorical_groups;
};

#endif // DATAFRAME_H