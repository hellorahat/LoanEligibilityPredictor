#include "acutest.h"
#include "DecisionTree.h"
#include <cmath>

void test_best_split(void) {
    DecisionTree tree;
    std::vector<std::vector<double>> features = {
        {64, 120, 1, 1}, {63, 125, 2, 1}, {66, 130, 2, 1}, {67, 140, 0, 1},
        {65, 150, 0, 1}, {68, 155, 2, 0}, {68, 165, 1, 1}, {72, 165, 2, 0},
        {66, 170, 0, 0}, {70, 180, 0, 0}, {74, 185, 1, 0}, {73, 210, 1, 0}
    };
    std::vector<int> labels = {1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0};
    auto result = tree.find_best_split(features, labels, 0, features.size(), 1);
    TEST_CHECK_(result.feature_index == 1 && result.threshold == 155, "Expected feature_index: 1 and threshold: 155, but got feature_index: %d and threshold: %f", result.feature_index, result.threshold);
}

void test_calculate_gini_index(void) {
    DecisionTree tree;
    // Simulating a split where left has three '1's and one '0', and right has only '1's
    map<double, int> left_counts = {{1.0, 3}, {0.0, 1}};
    map<double, int> right_counts = {{1.0, 4}};
    int left_size = 4;
    int right_size = 4;

    double gini_index = tree.calculate_gini_index(left_counts, right_counts, left_size, right_size);
    double expected_gini = (1.0 - (3.0/4.0)*(3.0/4.0) - (1.0/4.0)*(1.0/4.0)) * 4.0/8.0 + 
                           (1.0 - (4.0/4.0)*(4.0/4.0)) * 4.0/8.0;

    TEST_CHECK_(fabs(gini_index - expected_gini) < 1e-6, "Gini index expected to be %f, but got %f", expected_gini, gini_index);
}

void test_split_basic(void) {
    DecisionTree tree;
    vector<vector<double>> data = {{1, 3}, {2, 4}, {3, 5}, {4, 6}, {5, 7}};
    size_t split_index = tree.partition_data(data, 0, data.size(), 0, 3);
    TEST_CHECK(split_index == 3);
    TEST_CHECK(data[0][0] < 3 && data[1][0] < 3 && data[2][0] < 3);
    TEST_CHECK(data[3][0] >= 3 && data[4][0] >= 3);
}

void test_split_empty_dataset(void) {
    DecisionTree tree;
    vector<vector<double>> data = {{}};
    size_t split_index = tree.partition_data(data, 0, data.size(), 0, 3);
    TEST_CHECK(split_index == 0);
    TEST_CHECK(data.empty() || data[0].empty());
}

void test_split_single_feature(void) {
    DecisionTree tree;
    vector<vector<double>> data = {{1}, {2}, {3}, {4}, {5}};
    size_t split_index = tree.partition_data(data, 0, data.size(), 0, 3);
    TEST_CHECK(split_index == 3);
    TEST_CHECK(data[0][0] < 3 && data[1][0] < 3 && data[2][0] < 3);
    TEST_CHECK(data[3][0] >= 3 && data[4][0] >= 3);
}

void test_split_binary_feature(void) {
    DecisionTree tree;
    vector<vector<double>> data = {{1}, {0}, {1}, {1}, {1}, {0}};
    size_t split_index = tree.partition_data(data, 0, data.size(), 0, 0);
    TEST_CHECK(split_index == 2);
    TEST_CHECK(data[0][0] == 0 && data[1][0] == 0);
    TEST_CHECK(data[2][0] == 1 && data[3][0] == 1 && data[4][0] == 1 && data[5][0] == 1);
}

void test_split_not_possible(void) {
    DecisionTree tree;
    vector<vector<double>> data = {{1}, {1}, {1}, {1}, {1}, {1}};
    size_t split_index = tree.partition_data(data, 0, data.size(), 0, 0);
    TEST_CHECK(split_index == 3);
    TEST_CHECK(data[0][0] == 1 && data[1][0] == 1 && data[2][0] == 1);
    TEST_CHECK(data[3][0] == 1 && data[4][0] == 1 && data[5][0] == 1);
}

TEST_LIST = {
    {"test_split_basic", test_split_basic},
    {"test_split_empty_dataset", test_split_empty_dataset},
    {"test_split_single_feature", test_split_single_feature},
    {"test_split_binary_feature", test_split_binary_feature},
    {"test_split_not_possible", test_split_not_possible},
    { "best_split", test_best_split },
    { "test_calculate_gini_index", test_calculate_gini_index },
    { NULL, NULL }  // Terminate the list
};