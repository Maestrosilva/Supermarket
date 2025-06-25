#include "..//headers//Cashier.h"

Cashier::Cashier(const String& firstName, const String& lastName, const String& phoneNumber, unsigned char age, const String& password)
	: Worker(firstName, lastName, phoneNumber, age, password) {}

size_t Cashier::getTransactionCount() const { return this->transactionsCount; }

const Vector<Warning*>& Cashier::getWarnings() const { return this->warnings; }

bool Cashier::isApproved() const { return this->approved; }

void Cashier::approve() { approved = true; }

void Cashier::addWarning(Warning* const warning) {
    warnings.push(warning);
}

const Role& Cashier::getRole() const { return Role::CASHIER; }

void Cashier::serialize(std::ostream& os) const {
    Role::RoleEnum role = Role::CASHIER;
    os.write(reinterpret_cast<const char*>(&role), sizeof(role));
    Worker::serialize(os);
    os.write(reinterpret_cast<const char*>(&transactionsCount), sizeof(transactionsCount));
    size_t warningCount = warnings.getLength();
    os.write(reinterpret_cast<const char*>(&warningCount), sizeof(warningCount));
    for (size_t i = 0; i < warningCount; ++i) {
        warnings[i]->serialize(os);
    }
    os.write(reinterpret_cast<const char*>(&approved), sizeof(approved));
}

void Cashier::deserialize(std::istream& is) {
    Role::RoleEnum role;
    is.read(reinterpret_cast<char*>(&role), sizeof(role));
    Worker::deserialize(is);
    is.read(reinterpret_cast<char*>(&transactionsCount), sizeof(transactionsCount));
    size_t warningCount = 0;
    is.read(reinterpret_cast<char*>(&warningCount), sizeof(warningCount));
    for (size_t i = 0; i < warningCount; ++i) {
        Warning* w = new Warning();
        w->deserialize(is);
        warnings.push(w);
    }
    is.read(reinterpret_cast<char*>(&approved), sizeof(approved));
}

Cashier::~Cashier() {
    for (size_t i = 0; i < warnings.getLength(); i++) {
        delete warnings[i];
    }
    warnings.clear();
}