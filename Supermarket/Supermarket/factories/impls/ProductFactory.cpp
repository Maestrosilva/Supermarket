#include "..//headers//ProductFactory.h"

Product* ProductFactory::create(const ProductType& type, const String& name = "", const String& categoryId, double price = 0, double quantityOrWeight = 0) {
    switch (type.get()) {
    case ProductType::BY_UNIT: return new ProductsByUnit(name, categoryId, price, static_cast<size_t>(quantityOrWeight));
    case ProductType::BY_WEIGHT: return new ProductsByWeight(name, categoryId, price, quantityOrWeight);
    default:
        return nullptr;
    }
}