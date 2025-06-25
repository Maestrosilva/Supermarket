#include "..//headers//Category.h"

Category::Category(const String& name, const String& description)
    : name(name), description(description), id(String::intToString(IdGenerator::next(IdType::CATEGORY))) {
    if (description.isBlank()) {
        this->description = String("This is default description for ") + name;
    }
}

const String& Category::getName() const { return name; }

const String& Category::getId() const { return id; }

const String& Category::getDescription() const { return description; }

String Category::toString() const {
    return getName() + String(" - ") + getDescription();
}

void Category::serialize(std::ostream& os) const {
    id.serialize(os);
    name.serialize(os);
    description.serialize(os);
}

void Category::deserialize(std::istream& is) {
    id.deserialize(is);
    name.deserialize(is);
    description.deserialize(is);
}