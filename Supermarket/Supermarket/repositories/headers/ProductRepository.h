#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//models//headers//Product.h"
#include "..//..//factories//headers//ProductFactory.h"
#include "BaseRepository.h"
#include <fstream>

class ProductRepository : public BaseRepository {
private:
	Vector<Product*> products;
	static const String PRODUCTS_DATA_FILE_NAME;

	ProductRepository() = default;

	const Vector<Product*>& getProducts();
	Product* getById(const String& id);

	void add(Product* product);
	void remove(Product* const product);

	void load() override;
	void save() const override;
	void free() override;

	friend class System;
};