#include "..//headers//ProductByWeight.h"

ProductByWeight::ProductByWeight(const String& name, const String& categoryId, double price, double weight)
    : Product(name, categoryId, price), weight(weight) {}

double ProductByWeight::getQuantity() const { return weight; }

void ProductByWeight::updateQuantity(double toAdd) { weight += toAdd; }

const ProductType& ProductByWeight::getType() const {
    return ProductType::BY_WEIGHT;
}

String ProductByWeight::toString() const {
    return getName() + "(" + String::doubleToString(weight, 3) + String(" kg") + ") - " + String::doubleToString(price, 2) + String("lv.");
}

void ProductByWeight::serialize(std::ostream& os) const {
    Product::serialize(os);
    os.write(reinterpret_cast<const char*>(&weight), sizeof(weight));
}

void ProductByWeight::deserialize(std::istream& is) {
    Product::deserialize(is);
    is.read(reinterpret_cast<char*>(&weight), sizeof(weight));
}