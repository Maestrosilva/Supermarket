#pragma once
#include "..//..//core//enums//IdType.h"
#include "String.h"
#include "Serializable.h"
#include <fstream>

class IdGenerator : public Serializable {
public:
    static int next(IdType type);
    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;

private:
    static int counters[(int)IdType::COUNT];
};
