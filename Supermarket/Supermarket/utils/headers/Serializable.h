#pragma once
#include <iostream>

class Serializable {
public:
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;

    virtual ~Serializable() = default;
};