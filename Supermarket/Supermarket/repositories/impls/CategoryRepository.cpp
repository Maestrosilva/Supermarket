#include "..//headers//CategoryRepository.h"

const String CategoryRepository::CATEGORIES_DATA_FILE_NAME = "data//categories.dat";

const Vector<Category*>& CategoryRepository::getCategories() { return categories; }

Category* CategoryRepository::getById(const String& id) {
    for (size_t i = 0; i < categories.getLength(); i++) {
        if (categories[i]->getId() == id) {
            return categories[i];
        }
    }
    return nullptr;
}

Category* CategoryRepository::getByName(const String& name) {
    for (size_t i = 0; i < categories.getLength(); i++) {
        if (categories[i]->getName() == name) {
            return categories[i];
        }
    }
    return nullptr;
}

void CategoryRepository::add(Category* category) { categories.push(category); }
void CategoryRepository::remove(Category* const category) { categories.remove(category); }

void CategoryRepository::load() {
    free();
    std::ifstream file(CATEGORIES_DATA_FILE_NAME, std::ios::binary);
    if (!file) return;
    size_t length = 0;
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    for (size_t i = 0; i < length; i++) {
        Category* category = new Category();
        category->deserialize(file);
        categories.push(category);
        if (!file) break;
    }
    file.close();
}

void CategoryRepository::save() const {
    std::ofstream file(CATEGORIES_DATA_FILE_NAME, std::ios::binary | std::ios::trunc);
    if (!file) return;
    size_t length = categories.getLength();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    for (size_t i = 0; i < length; i++) {
        categories[i]->serialize(file);
    }
    file.close();
}

void CategoryRepository::free() {
    for (size_t i = 0; i < categories.getLength(); i++) {
        delete categories[i];
    }
    categories.clear();
}