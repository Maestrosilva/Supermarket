#pragma once
#include "..//..//..//utils//_Utils.h"

class Category : public Serializable {
private:
    String name;
    String description;

public:
    Category() = default;

    Category(const String& name, const String& description);

    Category(const Category& other);

    const String& getName() const;
    const String& getDescription() const;

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;
};