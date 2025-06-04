#pragma once
class Serializable {
    virtual void serialize(std::ostream& os) const = 0;
    virtual void deserialize(std::istream& is) = 0;

    virtual ~Serializable() = default;
};