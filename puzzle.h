//
// Created by Vlad Isan on 05/12/2023.
//

#ifndef PUZZLE_H
#define PUZZLE_H

#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "fmt/core.h"

constexpr uint64_t EXPANSION_SIZE = 999'999;

int puzzle_sample_1(const std::string &base_file_path);

uint64_t puzzle_sample_2(const std::string &base_file_path);

int puzzle_1(const std::string &base_file_path);

uint64_t puzzle_2(const std::string &base_file_path);

int do_puzzle_1(std::ifstream &file);

uint64_t do_puzzle_2(std::ifstream &file);

void expand_universe(std::vector<std::vector<int>> &grid);
int sum_shortest_distances(std::vector<std::vector<int>> &grid);

std::pair<std::vector<size_t>, std::vector<size_t>> find_expansion_points(const std::vector<std::vector<int>> &grid);
uint64_t sum_shortest_distances(const std::vector<std::vector<int>> &grid, const std::pair<std::vector<size_t>, std::vector<size_t>> &expansion_points);

#endif //PUZZLE_H
