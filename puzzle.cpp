//
// Created by Vlad Isan on 05/12/2023.
//

#include "puzzle.h"

int puzzle_sample_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

uint64_t puzzle_sample_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-sample-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int puzzle_1(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-1.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_1(file);
}

uint64_t puzzle_2(const std::string &base_file_path) {
    std::string file_path = fmt::format("{}/{}", base_file_path, "puzzle-input-2.txt");

    std::ifstream file(file_path);

    if (!file.is_open()) {
        fmt::println("{}", file_path);
        fmt::println("Something happened while opening the file. EAT DEEZNUTS!!!");
        fmt::println("Error {}", strerror(errno));

        return 0;
    }

    return do_puzzle_2(file);
}

int do_puzzle_1(std::ifstream &file) {
    std::string line;

    std::vector<std::vector<int>> grid;
    int galaxy_idx = 0;
    while (std::getline(file, line)) {
        std::vector<int> row;

        for (auto &c: line) {
            row.push_back(c == '#' ? ++galaxy_idx : 0);
        }

        grid.push_back(row);
    }

    expand_universe(grid);

    return sum_shortest_distances(grid);
}

uint64_t do_puzzle_2(std::ifstream &file) {
    std::string line;

    std::vector<std::vector<int>> grid;
    int galaxy_idx = 0;
    while (std::getline(file, line)) {
        std::vector<int> row;

        for (auto &c: line) {
            row.push_back(c == '#' ? ++galaxy_idx : 0);
        }

        grid.push_back(row);
    }

    auto expansion_points = find_expansion_points(grid);

    return sum_shortest_distances(grid, expansion_points);
}

void expand_universe(std::vector<std::vector<int>> &grid) {
    if (grid.empty()) {
        return;
    }

    // duplicate rows and columns whose only elements are 0

    std::vector<int> empty_rows{};
    std::vector<int> empty_cols{};

    // find empty rows
    for (int i = 0; i < grid.size(); ++i) {
        if (std::ranges::all_of(grid[i], [](int i) { return i == 0; })) {
            empty_rows.push_back(i);
        }
    }

    for (auto &row_idx: empty_rows | std::views::reverse) {
        grid.insert(grid.begin() + row_idx, grid[row_idx]);
    }

    // find empty columns
    for (int i = 0; i < grid[0].size(); ++i) {
        if (std::ranges::all_of(grid, [i](std::vector<int> &row) { return row[i] == 0; })) {
            empty_cols.push_back(i);
        }
    }

    for (auto &col_idx: empty_cols | std::views::reverse) {
        for (auto &row: grid) {
            row.insert(row.begin() + col_idx, 0);
        }
    }
}

int sum_shortest_distances(std::vector<std::vector<int>> &grid) {
    int sum = 0;

    std::vector<std::pair<int, int>> galaxy_positions{};

    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            if (grid[row][col] != 0) {
                galaxy_positions.emplace_back(row, col);
            }
        }
    }

    for (int i = 0; i < galaxy_positions.size(); ++i) {
        for (int j = i + 1; j < galaxy_positions.size(); ++j) {
            auto [row1, col1] = galaxy_positions[i];
            auto [row2, col2] = galaxy_positions[j];

            sum += std::abs(row1 - row2) + std::abs(col1 - col2);
        }
    }

    return sum;
}

std::pair<std::vector<size_t>, std::vector<size_t>> find_expansion_points(const std::vector<std::vector<int>> &grid) {
    std::pair<std::vector<size_t>, std::vector<size_t>> expansion_points{};

    // find empty rows
    for (int i = 0; i < grid.size(); ++i) {
        if (std::ranges::all_of(grid[i], [](int i) { return i == 0; })) {
            expansion_points.first.push_back(i);
        }
    }

    // find empty columns
    for (int i = 0; i < grid[0].size(); ++i) {
        if (std::ranges::all_of(grid, [i](const std::vector<int> &row) { return row[i] == 0; })) {
            expansion_points.second.push_back(i);
        }
    }

    return expansion_points;
}

uint64_t sum_shortest_distances(const std::vector<std::vector<int>> &grid,
                                const std::pair<std::vector<size_t>, std::vector<size_t>> &expansion_points) {
    uint64_t sum = 0;

    std::vector<std::pair<int, int>> galaxy_positions{};

    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[row].size(); ++col) {
            if (grid[row][col] != 0) {
                galaxy_positions.emplace_back(row, col);
            }
        }
    }

    for (int i = 0; i < galaxy_positions.size(); ++i) {
        for (int j = i + 1; j < galaxy_positions.size(); ++j) {
            auto [row1, col1] = galaxy_positions[i];
            auto [row2, col2] = galaxy_positions[j];

            auto row_expansions_between = std::ranges::count_if(expansion_points.first, [row1, row2](size_t row) { return row1 < row && row < row2; });

            auto col_expansions_between = std::ranges::count_if(expansion_points.second, [col1, col2](size_t col) { return (col1 < col && col < col2) || (col2 < col && col < col1); });

//            if (i == 0 && j == 2) {
//                fmt::println("Expansion points: ({}, {})", row_expansions_between, col_expansions_between);
//            }
//
//            fmt::println("Distance between ({}, {}) is {}", i, j, std::abs(row1 - row2) + std::abs(col1 - col2));

            sum += std::abs(row1 - row2) + (row_expansions_between * EXPANSION_SIZE) + std::abs(col1 - col2) + (col_expansions_between * EXPANSION_SIZE);
        }
    }

    return sum;
}
