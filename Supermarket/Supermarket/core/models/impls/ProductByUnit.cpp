#include "..//headers//ProductByUnit.h"

ProductsByUnit::ProductsByUnit(const String& name, const String& categoryId, double price, size_t quantity)
    : Product(name, categoryId, price), quantity(quantity) {}

double ProductsByUnit::getQuantity() const { return static_cast<double>(quantity); }

void ProductsByUnit::updateQuantity(double toAdd) { quantity += static_cast<size_t>(toAdd); }

const ProductType& ProductsByUnit::getType() const { return ProductType::BY_UNIT; }

String ProductsByUnit::toString() const {
    return getName() + "(" + String::intToString(quantity) + String("units") + ") - " + String::doubleToString(price, 2) + String("lv.");
}

void ProductsByUnit::serialize(std::ostream& os) const {
    Product::serialize(os);
    os.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
}

void ProductsByUnit::deserialize(std::istream& is) {
    Product::deserialize(is);
    is.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));
}