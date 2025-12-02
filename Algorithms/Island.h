#pragma once
#include "TVector.h"

class IslandMetricsAnalyzer {
    Tvector<Tvector<int>> dataMap;
    int verticalDimension;
    int horizontalDimension;

    bool coordinatesWithinBounds(int x, int y) const;
    int convertToLinearCoordinate(int x, int y) const;

public:
    explicit IslandMetricsAnalyzer(const Tvector<Tvector<int>>& inputMatrix);

    int computeConnectedComponents();
};s