#include "..//headers//ProductFactory.h"


Product* ProductFactory::create(const ProductType::Type type, const String& name, const Category& category, double price, double quantityOrWeight) {
    switch (type) {
    case ProductType::BY_UNIT: return new ProductsByUnit(name, category, price, static_cast<size_t>(quantityOrWeight));
    case ProductType::BY_WEIGHT: return new ProductsByWeight(name, category, price, quantityOrWeight);
    default:
        return nullptr;
    }
}