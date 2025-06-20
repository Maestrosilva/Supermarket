#pragma once
#include "Product.h"

class ProductByWeight : public Product {
private:
	double weight;

public:
	ProductByWeight() = default;
	ProductByWeight(const String& name, const String& categoryId, double price, double weight);

	double getQuantity() const override;
	void updateQuantity(double toAdd) override;

	const ProductType& getType() const override;
	String toString() const override;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	~ProductByWeight() = default;
};