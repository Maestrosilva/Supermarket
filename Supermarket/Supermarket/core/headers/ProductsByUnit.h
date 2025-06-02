#pragma once
#include "Product.h"

class ProductsByUnit : public Product {
private:
	size_t quantity;

public:
	ProductsByUnit() = default;
	ProductsByUnit(const String& name, const Category& category, double price, size_t quantity);

	double getQuantity() const override;
	void updateQuantity(double toAdd) override;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;
};