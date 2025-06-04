#include "..//headers//Product.h"

Product::Product(const String& name, const Category& category, double price) : name(name), category(category), price(price) {}

const String& Product::getName() const { return name; }

const Category& Product::getCategory() const { return category; }

double Product::getPrice() const { return price; }

void Product::serialize(std::ostream& os) const {
    name.serialize(os);
    category.serialize(os);
    os.write(reinterpret_cast<const char*>(&price), sizeof(price));
}

void Product::deserialize(std::istream& is) {
    name.deserialize(is);
    category.deserialize(is);
    is.read(reinterpret_cast<char*>(&price), sizeof(price));
}