#pragma once
#include "..//..//utils//headers//String.h"

class ProductType {
public:
    enum ProductTypeEnum {
        BY_UNIT,
        BY_WEIGHT
    };

    static ProductTypeEnum getRole(const String& type) {
        if (type.lowered() == "unit") {
            return BY_UNIT;
        }
        else if (type.lowered() == "weight") {
            return BY_WEIGHT;
        }
        else {
            throw std::invalid_argument("Type not found!");
        }
    }

    static String toString(const ProductType& type) {
        switch (type) {
        case ProductType::BY_UNIT: return "By Unit";
        case ProductType::BY_WEIGHT: return "By Weight";
        default: throw std::runtime_error("Invaid type!");
        }
    }
};