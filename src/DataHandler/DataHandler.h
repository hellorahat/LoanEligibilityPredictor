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
    /// @param index The index of the column to drop from the vector.
    /// @return A modified 2D vector with the specified column removed.
    std::vector<std::vector<std::string>> vector_drop_value(std::vector<std::vector<std::string>> data_vec, int index) {
        for (auto& row : data_vec) {
            if (index >= 0 && index < row.size()) {
                row.erase(row.begin() + index); // Erase element at the specified index
            }
        }
        return data_vec;
    }

    /// @brief Creates a one-hot vector given a 2D vector and a vector containing the column indexes of all categorical values
    /// @param data_vec The 2D vector to generate the one-hot vector from.
    /// @param categorical_indexes The column indexes of the categorical values.
    /// @return The one_hot_vector
    std::vector<std::vector<std::string>> one_hot_vector(std::vector<std::vector<std::string>> data_vec, std::vector<int> categorical_indexes) {
        
            
    }

    
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
        for(size_t i = 0; i < data_vec[1].size(); i++) { // we use index 1 instead of index 0 because index 0 contains the names, not the data contents
            const auto& cell = data_vec[1][i];
            if(!is_number(cell)) { // if the cell is not a number, we assume that it is a categorical value
                categorical_indexes.push_back(i);
            }
        }
        return categorical_indexes;
    }
    

    /// @brief Returns true if a string represents a number, false otherwise.
    /// @param s The string to check.
    /// @return bool indicating whether the string represents a number or not. (True if it is a number)
    bool is_number(std::string s) {
        try {
            std::size_t pos = 0;
            std::stoi(s, &pos);
            return pos==s.size();
        } catch(...) {
            return false; // conversion failed
        }
    }

};

#endif // DATAHANDLER_H