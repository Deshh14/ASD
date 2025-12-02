#include "Island.h"
#include "../lib_dsu/dsu.h"

IslandCounter::IslandCounter(const Tvector<Tvector<int>>& grid)
    : _grid(grid), _rows(grid.size()), _cols(grid.empty() ? 0 : grid[0].size()) {}

bool IslandCounter::isInBounds(int row, int col) const {
    return row >= 0 && row < _rows && col >= 0 && col < _cols;
}

int IslandCounter::convertToFlatIndex(int row, int col) const {
    return row * _cols + col;
}

int IslandCounter::calculateIslands() {
    if (_rows == 0 || _cols == 0) {
        return 0;
    }

    DSU disjointSet(_rows * _cols);

    const int neighborOffsets[2][2] = { {-1, 0}, {0, -1} };

    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            if (_grid[i][j] == 1) {
                int currentFlatIdx = convertToFlatIndex(i, j);

                for (int k = 0; k < 2; ++k) {
                    int neighborRow = i + neighborOffsets[k][0];
                    int neighborCol = j + neighborOffsets[k][1];

                    if (isInBounds(neighborRow, neighborCol) && _grid[neighborRow][neighborCol] == 1) {
                        int neighborFlatIdx = convertToFlatIndex(neighborRow, neighborCol);
                        disjointSet.unite(currentFlatIdx, neighborFlatIdx);
                    }
                }
            }
        }
    }

    int totalIslands = 0;
    Tvector<int> uniqueSetRoots(_rows * _cols);

    for (int i = 0; i < _rows; ++i) {
        for (int j = 0; j < _cols; ++j) {
            if (_grid[i][j] == 1) {
                int cellIndex = convertToFlatIndex(i, j);
                int rootRepresentative = disjointSet.find(cellIndex);

                bool rootAlreadyCounted = false;
                for (int idx = 0; idx < totalIslands; ++idx) {
                    if (uniqueSetRoots[idx] == rootRepresentative) {
                        rootAlreadyCounted = true;
                        break;
                    }
                }

                if (!rootAlreadyCounted) {
                    if (totalIslands >= uniqueSetRoots.size()) {
                        uniqueSetRoots.push_back(rootRepresentative);
                    }
                    else {
                        uniqueSetRoots[totalIslands] = rootRepresentative;
                    }
                    totalIslands++;
                }
            }
        }
    }

    return totalIslands;
}