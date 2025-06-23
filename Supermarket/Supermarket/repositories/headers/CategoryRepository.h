#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//models//headers//Category.h"
#include "BaseRepository.h"
#include <fstream>

class CategoryRepository : public BaseRepository {
private:
	Vector<Category*> categories;
	static const String CATEGORIES_DATA_FILE_NAME;

	CategoryRepository() = default;

	const Vector<Category*>& getCategories();
	Category* getById(const String& id);
	Category* getByName(const String& name);

	void add(Category* category);
	void remove(Category* const category);

	void load() override;
	void save() const override;
	void free() override;

	friend class System;
};