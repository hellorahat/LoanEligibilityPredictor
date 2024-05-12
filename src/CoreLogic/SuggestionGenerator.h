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
#include <../Includes/DataFrame.h>

class SuggestionGenerator {
    public:
    std::vector<double> get_closest_positive_prediction(std::vector<double> negative_point, DataFrame df) {
        
    }
};

#endif // SUGGESTIONGENERATOR_H