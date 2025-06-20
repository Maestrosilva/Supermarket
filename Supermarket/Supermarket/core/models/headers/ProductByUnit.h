#pragma once
#include "Product.h"

class ProductByUnit : public Product {
private:
	size_t quantity;

public:
	ProductByUnit() = default;
	ProductByUnit(const String& name, const String& categoryId, double price, size_t quantity);

	double getQuantity() const override;
	void updateQuantity(double toAdd) override;

	const ProductType& getType() const override;
	String toString() const override;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	~ProductByUnit() = default;
};