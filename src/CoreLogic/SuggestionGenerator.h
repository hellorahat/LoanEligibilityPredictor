/**
 * @file SuggestionGenerator.h
 * @author Rohan
 * @brief A header that generates suggestions on how an entry in a dataset can become classified as positive.
 * @version 0.1
 * @date 2024-05-12
 */

// Create header guard
#ifndef SUGGESTIONGENERATOR_H
#define SUGGESTIONGENERATOR_H

#include <iostream>
#include <vector>
#include <cmath>
#include "../Includes/DataFrame.h"

/// @brief For negatively classified predictions, this class finds the closest positive evaluation within the same categories (the credit policy and purpose will be the same) of the negative entries.
class SuggestionGenerator {
    public:
    /// @brief Returns the closest positive data point within the same categories of the negative data point.
    /// @param negative_point The negatively classified point.
    /// @param df The DataFrame object to search in.
    /// @return The closest positive data point within the same category.
    std::vector<double> get_closest_positive_prediction(std::vector<double> negative_point, DataFrame *df) {
        int curr_max_dist = -1;
        int curr_max_row_index = -1;
        for(int row = 0; row < df->get_normalized_vector().size(); row++) {
            // if the borrower didnt pay back the loan, we skip it
            if(!(df->paid_back_loan(row))) continue;

            std::vector<double> compared_point = df->get_normalized_vector()[row];

            // the borrower's information and the compared information need to be in the same categories
            // otherwise the data will be too irrelevant, so we skip it.
            if(!df->in_same_category(negative_point, compared_point)) continue;

            int distance = distance_between_points(negative_point, compared_point); // manhattan distance calculation
            if(distance > curr_max_dist) {
                curr_max_dist = distance;
                curr_max_row_index = row;
            }
        }
        return df->get_data_vec()[curr_max_row_index];
    }
    /// @brief Calculates the manhattan distance between two vectors.
    /// @param p1 Point 1
    /// @param p2 Point 2
    /// @return Distance between the two vectors.
    double distance_between_points(std::vector<double> p1, std::vector<double> p2) {
        double current_distance = 0.0;
        for(size_t col = 0; col < p1.size(); col++) {
            current_distance += std::abs(p1[col] - p2[col]);
        }
        return current_distance;
    }
};

#endif // SUGGESTIONGENERATOR_H