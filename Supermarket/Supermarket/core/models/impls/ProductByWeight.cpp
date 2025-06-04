#include "..//headers//ProductsByWeight.h"

ProductsByWeight::ProductsByWeight(const String& name, const Category& category, double price, double weight)
    : Product(name, category, price), weight(weight) {}

double ProductsByWeight::getQuantity() const { return weight; }

void ProductsByWeight::updateQuantity(double toAdd) { weight += toAdd; }

const ProductType& ProductsByWeight::getType() const {
    return ProductType::BY_WEIGHT;
}

void ProductsByWeight::serialize(std::ostream& os) const {
    Product::serialize(os);
    os.write(reinterpret_cast<const char*>(&weight), sizeof(weight));
}

void ProductsByWeight::deserialize(std::istream& is) {
    Product::deserialize(is);
    is.read(reinterpret_cast<char*>(&weight), sizeof(weight));
}