#pragma once
#include "..//..//utils//headers//String.h"
#include "..//..//utils//headers//Serializable.h"
#include "Category.h"

class Product : public Serializable {
protected:
	String name;
	Category category;
	double price;

public:
	Product() = default;
	Product(const String& name, const Category& category, double price)

	const String& getName() const;
	const Category& getCategory() const;
	double getPrice() const;

	virtual double getQuantity() const;
	virtual void updateQuantity(double toAdd);

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	virtual String toString() const;
	virtual ~Product() = default;
};