/**
 * @file DataHandler.h
 * @author Rohan
 * @brief A header that handles all data processing tasks for the application
 * @version 0.1
 * @date 2024-05-04
 */

// Create header guard
#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <cctype>
#include <regex>

class DataHandler {
    public:

    /// @brief Convert CSV into a 2D vector. More specifically, a vector containing a vector of strings.
    /// @param input_csv An input stream (std::ifstream) containing CSV data to be converted into a 2D vector. The CSV data should follow standard CSV format. The input stream should be open and ready for reading before calling this function.
    /// @return A 2D vector containing the CSV data converted into a structured format. Each element of the outer vector represents a row of the CSV data, and each element of the inner vectors represents a field (comma-separated value) of the corresponding row.
    std::vector<std::vector<std::string>> csv_to_vector(std::ifstream& input_csv) {
        std::vector<std::vector<std::string>> csv_data;
        std::string line;

        while(std::getline(input_csv, line)) {

            // split line into tokens using comma delimiter
            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> row;
            while(std::getline(iss, token, ',')) {
                if(token.empty()) { // replace empty values with "NULL"
                    row.push_back("NULL");
                } else {
                    row.push_back(token);
                }
            }

            // add the row to the 2d vector
            csv_data.push_back(row);
        }
        return csv_data;
    }

    /// @brief Drops a column from a vector.
    /// @param data_vec The 2D vector from which to drop the column. Each inner vector represents a row of data, and each element of the inner vectors represents a field (e.g., a comma-separated value).
    /// @param col_index The index of the column to drop from the vector.
    /// @return A modified 2D vector with the specified column removed.
    std::vector<std::vector<std::string>> vector_drop_column(std::vector<std::vector<std::string>> data_vec, int col_index) {
        for (auto& row : data_vec) {
            if (col_index >= 0 && col_index < row.size()) {
                row.erase(row.begin() + col_index); // Erase element at the specified index
            }
        }
        return data_vec;
    }

    /// @brief Drops a row from a vector.
    /// @param data_vec The 2D vector from which to drop the column. Each inner vector represents a row of data, and each element of the inner vectors represents a field (e.g., a comma-separated value).
    /// @param row_index The index of the row to drop from the vector.
    /// @return A modified 2D vector with the specified row removed.
    std::vector<std::vector<std::string>> vector_drop_row(std::vector<std::vector<std::string>> data_vec, int row_index) {
        std::cout << "Dropping row: " << row_index << std::endl;
        if (row_index >= 0 && row_index < data_vec.size()) {
            data_vec.erase(data_vec.begin() + row_index); // Erase row at the specified index
        }
        return data_vec;
    }

    /// @brief Cleans the dataset by removing strings from majority integer datasets and by removing integers from majority string datasets. This is intended to remove data entry mistakes. Also removes trailing whitespace and control characters from strings encountered.
    /// @param data_vec The 2D vector dataset to be cleaned.
    /// @return The cleaned 2D vector.
    std::vector<std::vector<std::string>> clean_vector_data(std::vector<std::vector<std::string>> data_vec) {
        for(size_t col = 0; col < data_vec[0].size(); col++) {
            int string_count = 0;
            int integer_count = 0;
            std::vector<int> integer_index_vector;
            std::vector<int> string_index_vector;

            for(size_t row = 1; row < data_vec.size(); row++) { // Skip the 0th row, since that just contains the column names
                std::string cell = data_vec[row][col];
                if(is_number(cell)) {
                    integer_count++;
                    integer_index_vector.push_back(row);
                } else {
                    string_count++;
                    string_index_vector.push_back(row);
                }
            }

            double total_count = string_count + integer_count;
            if((integer_count > 0) && (double)integer_count/total_count < .05) {
                std::cout << "Disparity found: " << data_vec[0][col] << std::endl;
                std::cout << "integer_count: " << integer_count << " / total_count: " << total_count << " = " << (double)integer_count/total_count << std::endl;
                for(int val : integer_index_vector) {
                    if(data_vec[val][col] == "NULL") continue;
                    vector_drop_row(data_vec, val);
                }
            }
            if((string_count > 0) && (double)string_count/total_count < .05) {
                std::cout << "Disparity found: " << data_vec[0][col] << std::endl;
                std::cout << "string_count: " << string_count << " / total_count: " << total_count << " = " << (double)string_count/total_count << std::endl;
                for(int val : string_index_vector) {
                    if(data_vec[val][col] == "NULL") continue;
                    vector_drop_row(data_vec, val);
                }
            }
        }
        return data_vec;
    }



    /// @brief Creates a one-hot vector given a 2D vector and a vector containing the column indexes of all categorical values
    /// @param data_vec The 2D vector to generate the one-hot vector from.
    /// @param categorical_indexes The column indexes of the categorical values.
    /// @return The one_hot_vector
    std::vector<std::vector<std::string>> one_hot_vector(std::vector<std::vector<std::string>> data_vec, std::vector<int> categorical_indexes) {
        // declare and initialize the variable to store the one hot vector
        std::vector<std::vector<std::string>> one_hot_vec;
        one_hot_vec.resize(data_vec.size());

        // create the new column names
        // index 0 of the 2D vector contains all of the column names
        for(size_t i = 0; i < data_vec[0].size(); i++) {
            std::string col_name = data_vec[0][i];
            auto it = std::find(categorical_indexes.begin(), categorical_indexes.end(), static_cast<int>(i));
            if(it != categorical_indexes.end()) {
                // is categorical

                // get unique category names for the selected column
                std::vector<std::string> category_name_vector = unique_category_names(data_vec, i);
                for(std::string category_name : category_name_vector) {
                    /*
                    create new header name with the category name appended to the column
                    e.g: ColumnName_CategoryName
                    */
                    one_hot_vec[0].push_back(trim_string(col_name) + "_" + trim_string(category_name)); 
                }
            } else {
                // not categorical
                one_hot_vec[0].push_back(col_name);
            }
        }

        // iterate through the data and fill in the one_hot_vector
        for(size_t col = 0; col < data_vec[0].size(); col++) {
            std::vector<std::string> category_name_vector = unique_category_names(data_vec, col);
            std::string column_name = data_vec[0][col];
            for(size_t row = 1; row < data_vec.size(); row++) { // skip the first row, since that contains the header with column names, not the data contents
                one_hot_vec[row].resize(one_hot_vec[0].size());
                auto it = std::find(categorical_indexes.begin(), categorical_indexes.end(), static_cast<int>(col));
                if(it != categorical_indexes.end()) {
                    // is categorical

                    // iterate through all unique categories
                    for(std::string category_name : category_name_vector) {
                        std::string one_hot_column_name = trim_string(column_name) + "_" + trim_string(category_name);
                        int one_hot_column_index = get_index_from_header_name(one_hot_vec, one_hot_column_name);
                        
                        // for each cateogry, fill in the data as "1" if the category matches, "0" otherwise
                        if(category_name == data_vec[row][col]) {
                            one_hot_vec[row][one_hot_column_index] = "1";
                            continue;
                        } else {
                            one_hot_vec[row][one_hot_column_index] = "0";
                            continue;
                        }
                    }

                } else {
                    // not categorical
                    std::string value = data_vec[row][col];
                    std::string column_name = data_vec[0][col];
                    int header_index = get_index_from_header_name(one_hot_vec, column_name);
                    one_hot_vec[row][header_index] = value;
                }
            }
        }

        return one_hot_vec;
    }

    /// @brief Fills in missing categorical data with the most occurring category, and fills in missing integer data with the mean.
    /// @param data_vec The 2D vector to impute.
    /// @param categorical_indexes A std::vector<int> containing the column indexes of all categorical values.
    /// @return The imputed 2D vector.
    std::vector<std::vector<std::string>> impute_data(std::vector<std::vector<std::string>> data_vec, std::vector<int> categorical_indexes) {
        for(size_t col = 0; col < data_vec[0].size(); col++) {
            auto it = std::find(categorical_indexes.begin(), categorical_indexes.end(), static_cast<int>(col));
            if(it != categorical_indexes.end()) { // is categorical
                /*
                    declare unordered_map to count occurrence, impute missing data with most occurring category
                    e.g: occurrence_map["Yes"] = 123, occurrence_map["No"] = 432 || Missing values will be replaced with "No" since it occured more often.
                */ 
                std::unordered_map<std::string, int> occurrence_map;

                // count occurrences
                for(size_t row = 1; row < data_vec.size(); row++) {
                    std::string cell = data_vec[row][col];
                    if(cell == "NULL") continue;
                    occurrence_map[cell]++;
                }
                
                // find the most occurring category
                std::string most_occurring_category = most_occurred_key_in_map(occurrence_map);

                // replace NULL values
                for(size_t row = 1; row < data_vec.size(); row++) {
                    if(data_vec[row][col] != "NULL") continue;
                    data_vec[row][col] = most_occurring_category;
                }

            } else { // not categorical
                // Replace non-categorical NULL values with the mean

                double sum = 0;
                size_t count = 0;
                // calculate mean
                for(size_t row = 1; row < data_vec.size(); row++) {
                    if(data_vec[row][col] == "NULL") continue;
                    try {
                        double cell = std::stod(data_vec[row][col]);
                        sum += cell;
                        count++;
                    } catch(...) {
                        continue;
                    }
                }
                // replace NULL values
                for(size_t row = 1; row < data_vec.size(); row++) {
                    if(data_vec[row][col] != "NULL") continue;
                    if(!count) { // avoid division by 0
                        data_vec[row][col] = "0"; 
                        continue;    
                    }
                    data_vec[row][col] = std::to_string(sum/count);
                }
            }
        }
        return data_vec;
    }

    /// @brief 
    /// @param data_vec 
    /// @param column_index 
    /// @return 
    std::vector<std::string> unique_category_names(std::vector<std::vector<std::string>> data_vec, int column_index) {
        std::unordered_set<std::string> unique_names;
        for (size_t row = 1; row < data_vec.size(); row++) {
            if (column_index >= 0 && column_index < data_vec[row].size()) {
                unique_names.insert(data_vec[row][column_index]);
            }
        }

        // Convert the set to a vector and return
        return std::vector<std::string>(unique_names.begin(), unique_names.end());
    }

    /// @brief Splits a dataset into two 2D vectors, one for training and one for testing.
    /// @param data_vec The 2D vector that contains the data.
    /// @param test_size The percentage of the data that will be used for testing, by default it is 20% (0.2).
    /// @return A pair containing the training and testing 2D vectors respectively.
    // std::pair<std::vector<std::vector<std::string>>,std::vector<std::vector<std::string>>> split_data(std::vector<std::vector<std::string>> data_vec, double test_size = 0.2) {
        
    // }

    
    /// @brief Returns all column names of a 2D vector that was created from a csv.
    /// @param data_vec The 2D vector to obtain the column names from.
    /// @return A std::vector<std::string> containing the column names.
    std::vector<std::string> vector_column_names(std::vector<std::vector<std::string>> data_vec) {
        return data_vec.front();
    }

    /// @brief Prints the contents of a 2D vector that was created from a csv.
    /// @param data_vec The 2D vector to print the contents of.
    void print_vector_data(std::vector<std::vector<std::string>> data_vec) {
        for (const auto& row : data_vec) {
            bool first_column = true; // comma won't be placed before first column
            for (const auto& cell : row) {
                if (!first_column) {
                    std::cout << ",";
                }
                std::cout << cell;
                first_column = false;
            }
            std::cout << std::endl;
        }
    }

    /// @brief Returns a vector<int> of the indexes of all categorical indexes found in a 2D vector.
    /// @param data_vec The 2D vector to find any categorical values from.
    /// @return A vector<int> containing all column indexes where categorical values exist.
    std::vector<int> get_categorical_indexes(std::vector<std::vector<std::string>> data_vec) {
        std::vector<int> categorical_indexes;

        for(size_t col = 0; col < data_vec[0].size(); col++) {
            for(size_t row = 1; row < data_vec.size(); row++) { // Skip the 0th row, since that just contains the column names
                std::string cell = data_vec[row][col];
                if(cell == "NULL") continue;
                if(!is_number(cell)) { // if a cell is found to not be a number, then we assume that it is a categorical value
                    categorical_indexes.push_back(col);
                    break;
                }
            }
        }
        return categorical_indexes;
    }
    
    private:
    /// @brief Returns true if a string represents a number, false otherwise.
    /// @param s The string to check.
    /// @return bool indicating whether the string represents a number or not. (True if it is a number)
    bool is_number(std::string s) {
        static const std::regex number_regex("^[-+]?[0-9]*\\.?[0-9]+$");
        return std::regex_match(s, number_regex);
    }

    // Function to trim trailing whitespace and control characters
    std::string trim_string(const std::string& str) {
        auto end = std::find_if(str.rbegin(), str.rend(), [](char c) {
            return !std::isspace(static_cast<unsigned char>(c)) && std::isprint(c);
        });
        return std::string(str.begin(), end.base());
    }


    std::string most_occurred_key_in_map(const std::unordered_map<std::string, int>& occurrence_map) {
        std::string most_occurred_key;
        int max_occurrences = 0;

        // Iterate through the map to find the key with maximum occurrences
        for (const auto& pair : occurrence_map) {
            if (pair.second > max_occurrences) {
                most_occurred_key = pair.first;
                max_occurrences = pair.second;
            }
        }

        return most_occurred_key;
    }
    
    int get_index_from_header_name(std::vector<std::vector<std::string>> data_vec, std::string column_name) {
        for(size_t col = 0; col < data_vec[0].size(); col++) {
            if(data_vec[0][col] == column_name) return col;
        }
        return -1;
    }

};

#endif // DATAHANDLER_H