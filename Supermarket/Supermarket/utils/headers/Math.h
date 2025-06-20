#pragma once
#include <cmath>

class Math {
public:
    static bool isWholeNumber(double value, double epsilon = 1e-6);

    static double applyDiscount(double price, double percent);
};
