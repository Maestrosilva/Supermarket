#include "..//headers//ProductByUnit.h"

ProductByUnit::ProductByUnit(const String& name, const String& categoryId, double price, size_t quantity)
    : Product(name, categoryId, price), quantity(quantity) {}

double ProductByUnit::getQuantity() const { return static_cast<double>(quantity); }

void ProductByUnit::updateQuantity(double toAdd) { quantity += static_cast<size_t>(toAdd); }

const ProductType& ProductByUnit::getType() const { return ProductType::BY_UNIT; }

String ProductByUnit::toString() const {
    return getName() + "(" + String::intToString(quantity) + String(" units") + ") - " + String::doubleToString(price, 2) + String("lv.");
}

void ProductByUnit::serialize(std::ostream& os) const {
    Product::serialize(os);
    os.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
}

void ProductByUnit::deserialize(std::istream& is) {
    Product::deserialize(is);
    is.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));
}