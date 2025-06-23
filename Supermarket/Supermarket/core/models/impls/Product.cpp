#include "..//headers//Product.h"

Product::Product(const String& name, const String& categoryId, double price) 
    : name(name), categoryId(categoryId), price(price), id(String::intToString(IdGenerator::next(IdType::PRODUCT))) {}

const String& Product::getId() const { return id; }

const String& Product::getName() const { return name; }

const String& Product::getCategoryId() const { return categoryId; }

double Product::getPrice() const { return price; }

void Product::serialize(std::ostream& os) const {
    id.serialize(os);
    name.serialize(os);
    categoryId.serialize(os);
    os.write(reinterpret_cast<const char*>(&price), sizeof(price));
}

void Product::deserialize(std::istream& is) {
    id.deserialize(is);
    name.deserialize(is);
    categoryId.deserialize(is);
    is.read(reinterpret_cast<char*>(&price), sizeof(price));
}