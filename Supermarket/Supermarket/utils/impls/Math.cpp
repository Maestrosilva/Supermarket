#include "..//headers//Math.h"

bool Math::isWholeNumber(double value, double epsilon) {
    return std::abs(value - std::round(value)) < epsilon;
}

double Math::applyDiscount(double price, double percent) {
    return price * (1.0 - percent / 100.0);
}