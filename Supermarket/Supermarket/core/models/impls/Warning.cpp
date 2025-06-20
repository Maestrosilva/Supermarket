#include "..//headers//Warning.h"

Warning::Warning(const Worker* sender, const String& description, const DegreeOfCriticality& degree)
    : senderId(sender->getId()), description(description) , degree(degree){}

const String& Warning::getSenderId() const { return senderId; }

const String& Warning::getDescription() const { return description; }

const DegreeOfCriticality& Warning::getDegreeOfCriticality() const { return degree; }


void Warning::serialize(std::ostream& os) const {
    senderId.serialize(os);
    description.serialize(os);
    os.write(reinterpret_cast<const char*>(&degree), sizeof(degree));
}

void Warning::deserialize(std::istream& is) {
    senderId.deserialize(is);
    description.deserialize(is);
    is.read(reinterpret_cast<char*>(&degree), sizeof(degree));
}