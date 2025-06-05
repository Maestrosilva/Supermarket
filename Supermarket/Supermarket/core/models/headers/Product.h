#pragma once
#include "..//..//..//utils//_Utils.h"
#include "..//..//enums//ProductType.h"
#include "Category.h"

class Product : public Serializable {
protected:
	String id;
	String name;
	String categoryId;
	double price;

public:
	Product() = default;
	Product(const String& name, const String& categoryId, double price);

	const String& getId() const;
	const String& getName() const;
	const String& getCategoryId() const;
	double getPrice() const;

	virtual double getQuantity() const = 0;
	virtual void updateQuantity(double toAdd) = 0;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	virtual const ProductType& getType() const = 0;
	virtual String toString() const = 0;

	virtual ~Product() = default;
};