#include "..//headers//WorkerFactory.h"

Worker* WorkerFactory::create(bool creational, const Role& role, const String& firstName, const String& lastName,
       const String& phoneNumber, unsigned char age, const String& password) {
    if (creational) {
        switch (role.get()) {
        case Role::CASHIER: return new Cashier(firstName, lastName, phoneNumber, age, password);
        case Role::MANAGER: return new Manager(firstName, lastName, phoneNumber, age, password);
        default:
            throw std::runtime_error("Unknown worker role in file.");
        }
    }
    else {
        switch (role.get()) {
        case Role::CASHIER: return new Cashier();
        case Role::MANAGER: return new Manager();
        default:
            throw std::runtime_error("Unknown worker role in file.");
        }
    }
}

Manager* WorkerFactory::promote(const Cashier* cashier) {
    if (cashier == nullptr) {
        throw std::runtime_error("Can't promote a nullptr!");
    }
    Manager* manager = new Manager();
    manager->setId(cashier->getId());
    manager->setFirstName(cashier->getFirstName());
    manager->setLastName(cashier->getLastName());
    manager->setPhoneNumber(cashier->getPhoneNumber());
    manager->setAge(cashier->getAge());
    return manager;
}