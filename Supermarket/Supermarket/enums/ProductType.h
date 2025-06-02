#pragma once
#include "..//utils//headers//String.h"

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