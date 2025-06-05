#include "..//headers//Warning.h"

Warning::Warning(const Worker* sender, const String& description)
    : senderId(sender->getId()), description(description) {}

const String& Warning::getSenderId() const { return senderId; }

const String& Warning::getDescription() const { return description; }

void Warning::serialize(std::ostream& os) const {
    senderId.serialize(os);
    description.serialize(os);
}

void Warning::deserialize(std::istream& is) {
    senderId.deserialize(is);
    description.deserialize(is);
}