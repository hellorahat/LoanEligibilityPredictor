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

/// @brief Provides an object to hold the different vectors used by the Random Forest Model. Also contains useful utility functions.
class DataFrame {
public:
    /// @brief Empty constructor
    DataFrame(){}

    /// @brief Constructor for a dataframe. It contains the feature_name_vec, data_vec, impute_vec, and categorical_groups.
    /// @param feature_names Vector of strings that contain the name of a column.
    /// @param data Vector of vector of doubles which contain the data contents. (One-hot encoded)
    /// @param impute_vals Vector of doubles that contain values to replace in the case of missing data. Numerical categories are replaced with mean. Categorical categories are replaced with mode.
    /// @param categories Intended for one-hot encoded categories. This is an unordered mapping which maps Columns(by their name) to a map of all of the column's categories(by their name) to all of its indexes. {"ColumnName1":{"CategoryName1":2},{"CategoryName2":3}}
    DataFrame(std::vector<std::string> feature_names, std::vector<std::vector<double>> data, std::vector<double> impute_vals, std::unordered_map<std::string, std::unordered_map<std::string, int>> categories) {
        feature_name_vec = feature_names;
        data_vec = data;
        impute_vec = impute_vals;
        categorical_groups = categories;
        normalized_vector = return_normalized_vec();
    }
    /// @brief Getter method for returning the feature name vector
    /// @return vector of strings for feature name vector. Indexed by columns
    std::vector<std::string> get_feature_name_vec() { return feature_name_vec; }

    /// @brief Returns vector<vector<double>> of data content
    /// @return Data content vector of vectors
    std::vector<std::vector<double>> get_data_vec() { return data_vec; }

    /// @brief Returns vector<double> of impute values
    /// @return Impute value vector
    std::vector<double> get_impute_vec() { return impute_vec; }

    void impute_data() {
        for(size_t row = 0; row < this->data_vec.size(); row++) {
            for(size_t col = 0; col < this->data_vec[0].size(); col++) {
                if(this->data_vec[row][col] == -1) this->data_vec[row][col] = this->impute_vec[col];
            }
        }
    }

        /**
     * @brief Column names are mapped to all of the categories in that column,
     *        all the categories are mapped to their index in the dataset vector.
     * @return Unordered map of string : (string : int)
     * @details 
     * - categorical_group["ColumnName1"] = ["category1"]:0, ["category2"]:1, ["category3"]:2              
     * - categorical_group["ColumnName2"] = ["category4"]:5, ["category5"]:6, ["category6"]:7
     * - categorical_group["purpose"]["debt_consolidation"] = COLUMN_INDEX (int)
     */
    std::unordered_map<std::string, std::unordered_map<std::string, int>> get_categorical_groups() { return categorical_groups; }

    /// @return Returns the normalized data content 
    std::vector<std::vector<double>> get_normalized_vector() { return normalized_vector; }

    /// @brief Normalizes a data by obtaining the sum of all columns and dividing each specific value by that sum.
    /// @param vec The vector to be normalized.
    /// @return A normalized version of the vector passed as the argument.
    std::vector<double> normalize(std::vector<double> vec) {
        std::vector<double> new_vec;
        double sum = 0;
        for(int col : get_all_numerical_columns()) {
            sum += vec[col];
        }
        for(size_t col = 0; col < vec.size(); col++) {
            if(is_categorical(col)) new_vec.push_back(vec[col]);
            else new_vec.push_back(vec[col]/sum);
        }
        return new_vec;
    }

    /// @brief Normalizes the 2D vector located in DataFrame.data_vec (which is the raw, one-hot encoded data content in the double data type)
    /// @return The normalized 2D vector.
    std::vector<std::vector<double>> return_normalized_vec() {
        std::vector<std::vector<double>> normalized_vec;
        for(size_t row = 0; row < this->data_vec.size(); row++) {
            std::vector<double> normalized_row;
            double sum = 0;
            for(size_t col : get_all_numerical_columns()) {
                sum += data_vec[row][col];
            }
            for(size_t col = 0; col < this->data_vec[row].size(); col++) {
                if(is_categorical(col)) normalized_row.push_back(this->data_vec[row][col]);
                else normalized_row.push_back(this->data_vec[row][col]/sum);
            }
            normalized_vec.push_back(normalized_row);
        }
        return normalized_vec;
    }

    /// @brief Given a feature name, returns the column index of that feature.
    /// @param feature_name A string value of the feature's name.
    /// @return The column index if feature was found. Returns -1 if not found.
    int get_col_index_from_feature_name(std::string feature_name) {
        for(int col = 0; col < this->feature_name_vec.size(); col++) {
            if(this->feature_name_vec[col] == feature_name) return col;
        }
        return -1;
    }

    /// @brief Given a column index, returns the feature name.
    /// @param index Column index
    /// @return Column name
    std::string get_feature_name_from_col_index(int index) { return feature_name_vec[index]; }
    
    /// @brief (For categorical columns) Given a column name, return all of the unique categories present in that column.
    /// @param col_name Name of the column.
    /// @return An unordered map of all the unique categories in that column. Each category is mapped to an int which represents their index in the dataset vector.
    std::unordered_map<std::string, int> get_categories_in_column(std::string col_name) { return this->categorical_groups[col_name]; }

    /// @brief (For one-hot encoded columns) Given a Column name, and the Category name which is present in the column. Return the column where that category is present.
    /// @param col_name The column name
    /// @param category_name The category in that column
    /// @return Column in the one-hot encoded dataset vector where the category is located.
    int get_column_index_of_category(std::string col_name, std::string category_name) { return this->categorical_groups[col_name][category_name]; }

    /// @brief (For one-hot encoded vectors) Gets the value of a category in a certain row.
    /// @param row Row index to look in.
    /// @param col_name Name of the Column.
    /// @param category_name Name of the Category in that column
    /// @return The double value thats located in the row for the specified category.
    double get_val_of_category(int row, std::string col_name, std::string category_name) { return this->data_vec[row][this->categorical_groups[col_name][category_name]]; }

    /// @brief Returns all columns in the one-hot encoded data vector that represent numerical values.
    /// @return Vector of ints of all column indexes
    std::vector<int> get_all_numerical_columns() {
        std::vector<int> col_vec;
        for(int col = 0; col < this->data_vec[0].size(); col++) {
            if(is_numerical(col)) col_vec.push_back(col);
        }
        return col_vec;
    }
    
    /// @brief Returns all columns in the one-hot encoded data vector that represent categorical values.
    /// @return Vector of ints of all column indexes
    std::vector<int> get_all_categorical_columns() {
        std::vector<int> col_vec;
        for(int col = 0; col < this->data_vec[0].size(); col++) {
            if(is_categorical(col)) col_vec.push_back(col);
        }
        return col_vec;
    }

    /// @brief Returns true if the column specified represents a numerical value
    /// @param col_index Column index to check
    /// @return True if numerical, false if categorical
    bool is_numerical(int col_index) {
        // iterate through all categorical groups. if col_index is not a match for all groups, then it is numerical
        for(auto group = this->categorical_groups.begin(); group != categorical_groups.end(); group++) {
            for(auto category = group->second.begin(); category != group->second.end(); category++) {
                if(col_index == category->second) return false;
            }
        }
        return true;
    }

    /// @brief Returns true if the column specified represents a categorical value
    /// @param col_index Column index to check
    /// @return True if categorical, false if numerical
    bool is_categorical(int col_index) {
        // iterate through all categorical groups. if col_index is a match for a group, then it is categorical
        for(auto group = this->categorical_groups.begin(); group != categorical_groups.end(); group++) {
            for(auto category = group->second.begin(); category != group->second.end(); category++) {                
                if(col_index == category->second) return true;
            }
        }
        return false;
    }

    /// @brief Checks if two data points belong to the same category group.
    /// @param p1 Data point 1
    /// @param p2 Data point 2
    /// @return True if they belong to the same category group. i.e: If they belong in the "purpose" group in the one-hot encoded vector.
    bool in_same_category(std::vector<double> p1, std::vector<double> p2) {
        for(int col : get_all_categorical_columns()) {
            if(p1[col]!=p2[col]) return false;
        }
        return true;
    }

    /// @brief Returns if the borrower paid back the loan.
    /// @param row Row index to check
    /// @return True if the borrower paid back the loan on time, false if they didn't pay the loan back on time.
    bool paid_back_loan(int row) { return this->data_vec[row].back() == 0; }

private:
    std::vector<std::vector<double>> normalized_vector;

    /// @brief Vector of strings that contain the name of a column.
    std::vector<std::string> feature_name_vec;

    /// @brief Vector of vector of doubles which contain the data contents. (One-hot encoded)
    std::vector<std::vector<double>> data_vec;

    /// @brief Vector of doubles that contain values to replace in the case of missing data. Numerical categories are replaced with mean. Categorical categories are replaced with mode.
    std::vector<double> impute_vec;

    /// @brief Intended for one-hot encoded categories. This is an unordered mapping which maps Columns(by their name) to a map of all of the column's categories(by their name) to all of its indexes. {"ColumnName1":{"CategoryName1":2},{"CategoryName2":3}}
    std::unordered_map<std::string, std::unordered_map<std::string, int>> categorical_groups;
};

#endif // DATAFRAME_H