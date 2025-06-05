#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//enums//ProductType.h"
#include "..//..//core//models//headers//Product.h"
#include "..//..//core//models//headers//ProductByUnit.h"
#include "..//..//core//models//headers//ProductByWeight.h"
#include <fstream>
#include <stdexcept>

class ProductFactory {
public:
    static Product* create(const ProductType& type, const String& name = "", const String& categoryId = "", double price = 0, double quantityOrWeight = 0);
};