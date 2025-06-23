#pragma once
#include "..//..//core//enums//IdType.h"
#include "String.h"
#include "Serializable.h"
#include <fstream>

class IdGenerator {
public:
    static int next(IdType type);
    static void rollback(IdType type);
    static void serialize(std::ostream& os);
    static void deserialize(std::istream& is);

private:
    static int counters[(int)IdType::COUNT];
};
