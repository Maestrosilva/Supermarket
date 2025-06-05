#pragma once
#include "..//..//utils//headers//String.h"
#include <stdexcept>

class Role {
public:
    enum RoleEnum {
        CASHIER,
        MANAGER
    };

private:
    RoleEnum role;

public:
    Role(RoleEnum r) : role(r) {}

    RoleEnum get() const {
        return role;
    }

    static String toString(const Role& role) {
        switch (role.get()) {
        case CASHIER: return "Cashier";
        case MANAGER: return "Manager";
        default: return "Unknown";
        }
    }

    static Role get(const String& type) {
        if (type.lowered() == String("cashier")) { return Role::CASHIER; }
        else if (type.lowered() == String("manager")) { return Role::MANAGER; }
        else { throw std::invalid_argument("Invalid type!"); }
    }

    bool operator==(const Role& other) const {
        return role == other.role;
    }
};