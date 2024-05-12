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
#include <unordered_map>
#include <cctype>
#include <regex>
#include <random>

class DataHandler {
    public:

    std::tuple<std::vector<std::string>, std::vector<std::vector<double>>, std::vector<double>> process_data(std::ifstream& input_csv, std::vector<int> categorical_indexes) {
        // declare and initialize data_vec
        std::vector<std::vector<std::string>> data_vec;
        data_vec = csv_to_vector(input_csv);
        // declare the vectors that will be returned
        std::vector<std::string> feature_name_vec;
        std::vector<std::vector<double>> double_vec;
        std::vector<double> impute_vec;

        // modify data_vec to have one-hot encodings for all categorical columns.
        std::vector<std::unordered_map<std::string, int>> categorical_groups;
        int total_vectors_added = 0; // keep track of total vectors added to keep indexing consistent
        for(int index : categorical_indexes) {
            std::pair<std::vector<std::vector<std::string>>, std::unordered_map<std::string, int>> encoding_pair = one_hot_encoding(data_vec, index+total_vectors_added);
            std::vector<std::vector<std::string>> one_hot_vec = encoding_pair.first;
            std::unordered_map<std::string, int> one_hot_col_index = encoding_pair.second; // one_hot_col_index["categoryname"] = index

            // drop the column as we will be inputting the one_hot_vec in its place
            data_vec = vector_drop_column(data_vec, index+total_vectors_added);

            // for each row, insert the one-hot encoding into the index
            for(int row = 0; row < one_hot_vec.size(); row++) {
                // insert the one-hot encoded data into the specified index
                auto it = data_vec[row].begin() + index+total_vectors_added;
                data_vec[row].insert(it, one_hot_vec[row].begin(), one_hot_vec[row].end());
            }

            // now that the one_hot_vec has been merged to the source vector, we need to update the mappings
            for(auto it = one_hot_col_index.begin(); it != one_hot_col_index.end(); it++) {
                it->second += index+total_vectors_added;
            }

            total_vectors_added += one_hot_vec[0].size()-1; // need to keep track of all vectors added to keep indexing correct. "-1" because we also dropped a column earlier.
            std::cout << "vectors added: " << total_vectors_added << std::endl;

            categorical_groups.push_back(one_hot_col_index); // push the updated mappings into the categorical groups for future reference

        }

        // set the feature_name_vec to the header
        feature_name_vec = data_vec[0];

        // drop the header (which contains the column names) and create a vector<vector<double>> that contains only the row entries of data.
        // this is done so we can input double data type into random forest model
        double_vec = vector_convert_to_double(vector_drop_row(data_vec,0));        

        // impute_vec will contain the values that will be replaced in the case of missing data in a user's input
        impute_vec.resize(double_vec[0].size());

        // -1 means that the column was not given a replacement value yet
        for(size_t col = 0; col < impute_vec.size(); col++) {
            impute_vec[col] = -1;
        }

        // set impute_vec values for category groups first, the value given will be the mode
        for(int i = 0; i < categorical_groups.size(); i++) {
            // for each category group
            // keep track of current max for each index
            int curr_max = -1;
            int max_index = -1;
            for(auto it = categorical_groups[i].begin(); it != categorical_groups[i].end(); it++) {
                int col = it->second;
                std::cout<<"col:"<<col<<std::endl;
                for(int row = 0; row < double_vec.size(); row++) {
                    if(impute_vec[col] == -1) impute_vec[col] = 0;
                    impute_vec[col]++;
                    if(impute_vec[col] > curr_max) {
                        curr_max = impute_vec[col];
                        max_index = col;
                    }
                }
            }

            // iterate through all columns of the category group. If col is the max_index, set it to 1; set to 0 otherwise.
            for(auto it = categorical_groups[i].begin(); it != categorical_groups[i].end(); it++) {
                int col = it->second;
                std::cout<<"Group:"<<i<<"\tCol:"<<it->first<<"\tIndex:"<<it->second<<std::endl;
                if(col == max_index) {
                    impute_vec[col] = 1;
                }
                else
                    impute_vec[col] = 0;
            }

            std::cout<<"------------------------"<<std::endl;
        }

        // now set impute_vec values for numerical columns, the value given will be the mean for the column
        for(size_t col = 0; col < impute_vec.size(); col++) {
            if(impute_vec[col] != -1) continue; // if the value was already given (for categorical group) we skip the column
            for(size_t row = 0; row < double_vec.size(); row++) {
                if(impute_vec[col] == -1) impute_vec[col] = 0;
                impute_vec[col] += double_vec[row][col];
            }
            impute_vec[col] /= double_vec.size();
        }

        for(size_t col = 0; col < impute_vec.size(); col++) {
            std::cout << "Col: " << col << "\tVal: " << impute_vec[col] << std::endl;
        }

        return std::make_tuple(feature_name_vec, double_vec, impute_vec);
    }

    /// @brief Convert CSV into a 2D vector. More specifically, a vector containing a vector of strings.
    /// @param input_csv An input stream (std::ifstream) containing CSV data to be converted into a 2D vector. The CSV data should follow standard CSV format. The input stream should be open and ready for reading before calling this function.
    /// @return A 2D vector containing the CSV data converted into a structured format. Each element of the outer vector represents a row of the CSV data, and each element of the inner vectors represents a field (comma-separated value) of the corresponding row.
    std::vector<std::vector<std::string>> csv_to_vector(std::ifstream& input_csv) {
        std::vector<std::vector<std::string>> csv_data;

        // Iterate lines using istream_iterator
        for(std::istream_iterator<std::string> it(input_csv); it != std::istream_iterator<std::string>(); ++it) {
            std::string line = *it;

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

    // vector_to_csv for vector<vector<string>>
    void vector_to_csv(std::vector<std::vector<std::string>> data_vec, std::string csv_name) {
        std::ofstream myfile;
        myfile.open(csv_name + ".csv");
        for(size_t row = 0; row < data_vec.size(); row++) {
            for(size_t col = 0; col < data_vec[0].size(); col++) {
                myfile << data_vec[row][col];
                if(col != data_vec[0].size()-1) myfile << ",";
            }
            myfile << std::endl;
        }
        myfile.close();
    }
    // vector_to_csv for vector<string>, vector<vector<double>>
    void vector_to_csv(std::vector<std::string> feature_names, std::vector<std::vector<double>> double_vec, std::string csv_name) {
        std::ofstream myfile;
        myfile.open(csv_name + ".csv");
        for(size_t col = 0; col < feature_names.size(); col++) {
            myfile << feature_names[col];
            if(col != feature_names.size()-1) myfile << ",";
        }
        myfile << std::endl;
        for(size_t row = 0; row < double_vec.size(); row++) {
            for(size_t col = 0; col < double_vec[0].size(); col++) {
                myfile << double_vec[row][col];
                if(col != double_vec[0].size()-1) myfile << ",";
            }
            myfile << std::endl;
        }
        myfile.close();
    }

    // vector_to_csv for vector<vector<double>>
    void vector_to_csv(std::vector<std::vector<double>> data_vec, std::string csv_name) {
        std::ofstream myfile;
        myfile.open(csv_name + ".csv");
        for(size_t row = 0; row < data_vec.size(); row++) {
            for(size_t col = 0; col < data_vec[0].size(); col++) {
                myfile << data_vec[row][col];
                if(col != data_vec[0].size()-1) myfile << ",";
            }
            myfile << std::endl;
        }
        myfile.close();
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
        if (row_index >= 0 && row_index < data_vec.size()) {
            data_vec.erase(data_vec.begin() + row_index); // Erase row at the specified index
        }
        return data_vec;
    }

    /// @brief Cleans the dataset by removing strings from majority integer datasets and by removing integers from majority string datasets. This is intended to remove data entry mistakes.
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

    std::vector<std::vector<double>> vector_convert_to_double(std::vector<std::vector<std::string>> data_vec) {
        // declare variable to hold the converted vector
        std::vector<std::vector<double>> double_vec;

        // convert each entry into double
        for(size_t row = 0; row < data_vec.size(); row++) {
            std::vector<double> doubleRow;
            for(size_t col = 0; col < data_vec[row].size(); col++) {
                try {
                    double val = std::stod(data_vec[row][col]); // this variable will hold the converted value
                    doubleRow.push_back(val);
                } catch(...) {
                    doubleRow.push_back(0.0); // if conversion failed, place 0.0 instead
                    std::cout << "Conversion error: " << data_vec[row][col];
                }
            }
            double_vec.push_back(doubleRow);
        }
        return double_vec;
    }

    std::pair<std::vector<std::vector<std::string>>, std::unordered_map<std::string, int>> one_hot_encoding(std::vector<std::vector<std::string>> data_vec, int categoricalIndex) {
        // declare the one hot encoding vector
        std::vector<std::vector<std::string>> one_hot_vec;
        // the encoding has the same amount of rows as the source data vector
        one_hot_vec.resize(data_vec.size());
        // the amount of columns in the one_hot_vec depends on how much unique categories the categorical column has
        std::vector<std::string> unique_category_vector = unique_category_names(data_vec, categoricalIndex);
        for(int i = 0; i < one_hot_vec.size(); i++) {
            one_hot_vec[i].resize(unique_category_vector.size());
        }

        // label row 0 of one_hot_vec with the new column names
        std::string column_name = data_vec[0][categoricalIndex];
        std::unordered_map<std::string, int> one_hot_col_index; // one_hot_col_index["CategoryName"] = column_index
        for(size_t i = 0; i < unique_category_vector.size(); i++) {
            std::string category_name = unique_category_vector[i];
            std::string one_hot_col_name = column_name + ":" + category_name;
            one_hot_vec[0][i] = one_hot_col_name;
            one_hot_col_index[category_name] = i;
        }

        // fill in the rest of the rows
        for(size_t row = 1; row < one_hot_vec.size(); row++) { // start at row 1 to iterate every row except the header (which contain the column names)
            std::string category_name = data_vec[row][categoricalIndex]; // retrieve the category name from the row
            int index = one_hot_col_index[category_name]; // retrieve the column index in our one hot vector for the category name
            for(int col = 0; col < unique_category_vector.size(); col++) {
                // if we are at the correct index, put 1, else 0
                if(col==index)
                    one_hot_vec[row][col] = "1";
                else
                    one_hot_vec[row][col] = "0";
            }
        }

        return std::make_pair(one_hot_vec, one_hot_col_index);
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
            std::cout << pair.first << std::endl;
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