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

class SuggestionGenerator {
    public:
    std::vector<double> get_closest_positive_prediction(std::vector<double> negative_point, DataFrame *df) {
        int curr_max_dist = -1;
        int curr_max_row_index = -1;
        for(int row = 0; row < df->get_data_vec().size(); row++) {
            // if the borrower didnt pay back the loan, we skip it
            if(!(df->paid_back_loan(row))) continue;

            std::vector<double> compared_point = df->get_data_vec()[row];

            if(!df->in_same_category(negative_point, compared_point)) continue;

            int distance = distance_between_points(negative_point, compared_point);
            if(distance > curr_max_dist) {
                curr_max_dist = distance;
                curr_max_row_index = row;
            }
        }
        return df->get_data_vec()[curr_max_row_index];
    }
    double distance_between_points(std::vector<double> p1, std::vector<double> p2) {
        double current_distance = 0.0;
        for(size_t col = 0; col < p1.size(); col++) {
            current_distance += std::abs(p1[col] - p2[col]);
        }
        return current_distance;
    }
};

#endif // SUGGESTIONGENERATOR_H