#include "..//headers//Category.h"

Category::Category(const String& name, const String& description)
    : name(name), description(description), id(IdGenerator::next(IdType::CATEGORY)) {
    if (!description) {
        this->description = String("This is default description for") + name;
    }
}

const String& Category::getName() const { return name; }

const String& Category::getId() const { return id; }

const String& Category::getDescription() const { return description; }

void Category::serialize(std::ostream& os) const {
    name.serialize(os);
    description.serialize(os);
}

void Category::deserialize(std::istream& is) {
    name.deserialize(is);
    description.deserialize(is);
}