#include "TVector.h"

class IslandCounter {
private:
    Tvector<Tvector<int>> _grid;
    int _rows;
    int _cols;

    bool isInBounds(int row, int col) const;
    int convertToFlatIndex(int row, int col) const;

public:
    IslandCounter(const Tvector<Tvector<int>>& grid);

    int calculateIslands();
};