#pragma once
#include "..//utils//headers//String.h"

class Role {
public:
    enum RoleEnum {
        CASHIER,
        MANAGER
    };

    static RoleEnum getRole(const String& role) {
        if (role.lowered() == "cashier") {
            return CASHIER;
        }
        else if (role.lowered() == "manager") {
            return MANAGER;
        }
        else {
            throw std::invalid_argument("Role not found!");
        }
    }