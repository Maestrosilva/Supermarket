#include "..//headers//Worker.h"

Worker::Worker(const String& firstName, const String& lastName, const String& phoneNumber, unsigned char age, const String& password) 
	: id(String::intToString(IdGenerator::next(IdType::WORKER))), firstName(firstName), lastName(lastName), phoneNumber(phoneNumber),
	age(age), password(Hasher::hash(password)) {}

const String& Worker::getId() const { return this->id; }

const String& Worker::getFirstName() const { return this->firstName; }

const String& Worker::getLastName() const { return this->lastName; }

const String& Worker::getPhoneNumber() const { return this->phoneNumber; }

void Worker::setFirstName(const String& firstName) { this->firstName = firstName; }

void Worker::setLastName(const String& lastName) { this->lastName = lastName; }

void Worker::setPhoneNumber(const String& phoneNumber) { this->phoneNumber = phoneNumber; }

void Worker::setAge(unsigned char age) { this->age = age; }

void Worker::setId(const String& id) { this->id = id; }

void Worker::setPassword(const String& password) { this->password = password; }

String Worker::toString() const {
    String toReturn;
    toReturn.append("Id: ").append(id).append(" ");
    Role role = getRole();
    toReturn.append(Role::toString(role)).append(" ");
    toReturn.append(firstName).append(" ");
    toReturn.append(lastName).append(" ");
    toReturn.append(phoneNumber).append(" ");
    toReturn.append(String::intToString(age)).append(" years old");
    return toReturn;
}

unsigned char Worker::getAge() const { return this->age; }

void Worker::serialize(std::ostream& os) const {
    id.serialize(os);
    firstName.serialize(os);
    lastName.serialize(os);
    phoneNumber.serialize(os);
    os.write(reinterpret_cast<const char*>(&age), sizeof(age));
    password.serialize(os);
}

void Worker::deserialize(std::istream& is) {
    id.deserialize(is);
    firstName.deserialize(is);
    lastName.deserialize(is);
    phoneNumber.deserialize(is);
    is.read(reinterpret_cast<char*>(&age), sizeof(age));
    password.deserialize(is);
}

Worker::~Worker() = default;