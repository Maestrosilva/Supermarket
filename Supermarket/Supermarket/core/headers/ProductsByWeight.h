#pragma once
#include "Product.h"

class ProductsByWeight : public Product {
private:
	double weight;

public:
	ProductsByWeight() = default;
	ProductsByWeight(const String& name, const Category& category, double price, double weight);

	double getQuantity() const override;
	void updateQuantity(double toAdd) override;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;
};