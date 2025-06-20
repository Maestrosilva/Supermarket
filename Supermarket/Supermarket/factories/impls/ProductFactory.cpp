#include "..//headers//ProductFactory.h"

Product* ProductFactory::create(bool creational, const ProductType& type, const String& name, const String& categoryId, double price, double quantityOrWeight) {
    if (creational) {
        switch (type.get()) {
        case ProductType::BY_UNIT: return new ProductByUnit(name, categoryId, price, static_cast<size_t>(quantityOrWeight));
        case ProductType::BY_WEIGHT: return new ProductByWeight(name, categoryId, price, quantityOrWeight);
        default:
            return nullptr;
        }
    }
    else {
        switch (type.get()) {
        case ProductType::BY_UNIT: return new ProductByUnit();
        case ProductType::BY_WEIGHT: return new ProductByWeight();
        default:
            return nullptr;
        }
    }
}