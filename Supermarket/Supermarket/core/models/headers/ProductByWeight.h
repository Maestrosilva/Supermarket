#pragma once
#include "Product.h"

class ProductsByWeight : public Product {
private:
	double weight;

public:
	ProductsByWeight() = default;
	ProductsByWeight(const String& name, const String& categoryId, double price, double weight);

	double getQuantity() const override;
	void updateQuantity(double toAdd) override;

	const ProductType& getType() const override;
	String toString() const override;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;


	~ProductsByWeight() = default;
};