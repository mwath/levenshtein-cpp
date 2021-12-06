#include "levenshtein.hpp"
#include <algorithm>
#include <cstdint>
#include <cstring>

namespace lev {
int distance(std::string a, std::string b) {
    const int rows = a.length();
    const int cols = b.length();

    if (rows == 0)
        return cols;

    if (cols == 0)
        return rows;

    uint16_t matrix[rows][cols];
    std::memset(matrix, 0, rows * cols * sizeof(uint16_t));

    for (auto i = 0; i < rows; ++i)
        matrix[i][0] = i;

    for (auto i = 0; i < cols; ++i)
        matrix[0][i] = i;

    for (auto j = 1; j < cols; ++j) {
        for (auto i = 1; i < rows; ++i) {
            matrix[i][j] = std::min({
                matrix[i - 1][j] + 1, // deletion
                matrix[i][j - 1] + 1, // insertion
                matrix[i - 1][j - 1] + (a[i - 1] != b[j - 1]) // substitution
            });
        }
    }

    return matrix[rows - 1][cols - 1];
}
} // namespace lev
