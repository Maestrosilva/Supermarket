#include "..//headers//WorkerFactory.h"

Worker* WorkerFactory::create(const Role& role, const String& firstName, const String& lastName,
	const String& phoneNumber, unsigned char age, const String& password) {
    switch (role) {
    case Role::CASHIER: return = new Cashier(firstName, lastName, phoneNumber, age, password);
    case Role::MANAGER: return new Manager(firstName, lastName, phoneNumber, age, password);
    default:
        throw std::runtime_error("Unknown worker role in file.");
    }
}