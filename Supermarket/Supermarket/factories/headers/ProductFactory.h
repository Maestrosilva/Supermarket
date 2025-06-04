#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//enums//ProductType.h"
#include "..//..//core//models//headers//Product.h"
#include "..//..//core//models//headers//ProductsByUnit.h"
#include "..//..//core//models//headers//ProductsByWeight.h"
#include <fstream>
#include <stdexcept>

class ProductFactory {
public:
    static Product* create(const ProductType& type, const String& name, const Category& category, double price = 0, double quantityOrWeight = 0);
};