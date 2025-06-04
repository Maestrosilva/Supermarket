#include "..//headers//Category.h"

Category::Category(const String& name, const String& description)
    : name(name), description(description) {}

Category::Category(const Category& other)
    : name(other.name), description(other.description) {}

const String& Category::getName() const { return name; }

const String& Category::getDescription() const { return description; }

void Category::serialize(std::ostream& os) const {
    name.serialize(os);
    description.serialize(os);
}

void Category::deserialize(std::istream& is) {
    name.deserialize(is);
    description.deserialize(is);
}