#pragma once
#include "..//..//enums//IdType"
#include "String.h"
#include "Serializable.h"
#include <fstream>

class IdGenerator : public Serializable {
public:
    static int next(IdType type);

    void serialize(const std::string& filename) const override;
    void deserialize(const std::string& filename) override;

private:
    static int counters[(int)IdType::Count];
};

int IdGenerator::counters[(int)IdType::Count] = { 0 };