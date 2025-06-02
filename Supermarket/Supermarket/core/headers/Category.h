#pragma once
#include "..//..//utils//headers//String.h"

class Category {
private:
	String name;
	String description;

public:
	Category() = default;
	Category(const String& name, const String& description);

	String& getName() const;
	String& getDescription() const;
};