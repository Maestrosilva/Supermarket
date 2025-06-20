#include "..//headers//Manager.h"

const String Manager::specialCode = "SPEZIALEN_E";

Manager::Manager(const String& firstName, const String& lastName, const String& phoneNumber, unsigned char age, const String& password)
	: Worker(firstName, lastName, phoneNumber, age, password) {}

const Role& Manager::getRole() const { return Role::MANAGER; }

bool Manager::authenticate(const String& specialCode) { return Manager::specialCode == specialCode; }

void Manager::serialize(std::ostream& os) const {
    Role::RoleEnum role = Role::MANAGER;
    os.write(reinterpret_cast<const char*>(&role), sizeof(role));
    Worker::serialize(os);
}

void Manager::deserialize(std::istream& is) {
    Role::RoleEnum role;
    is.read(reinterpret_cast<char*>(&role), sizeof(role));
    Worker::deserialize(is);
}