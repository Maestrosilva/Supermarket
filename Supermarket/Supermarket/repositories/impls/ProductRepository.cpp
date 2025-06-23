#include "..//headers//ProductRepository.h"

const String ProductRepository::PRODUCTS_DATA_FILE_NAME = "data//products.dat";

const Vector<Product*>& ProductRepository::getProducts() { return products; }

Product* ProductRepository::getById(const String& id) {
    for (size_t i = 0; i < products.getLength(); i++) {
        if (products[i]->getId() == id) {
            return products[i];
        }
    }
    return nullptr;
}

Vector<Product*> ProductRepository::getByCategoryId(const String& id) {
    Vector<Product*> vect;
    for (size_t i = 0; i < products.getLength(); i++) {
        if (products[i]->getCategoryId() == id) {
            return vect.push(products[i]);
        }
    }
    return vect;
}

Product* ProductRepository::getByName(const String& name) {
    for (size_t i = 0; i < products.getLength(); i++) {
        if (products[i]->getName() == name) {
            return products[i];
        }
    }
    return nullptr;
}

void ProductRepository::add(Product* product) { products.push(product); }
void ProductRepository::remove(Product* product) { products.remove(product); }

void ProductRepository::load() {
    free();
    std::ifstream file(ProductRepository::PRODUCTS_DATA_FILE_NAME, std::ios::binary);
    if (!file) return;
    size_t length = 0;
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    for (size_t i = 0; i < length; ++i) {
        char typeByte = 0;
        file.read(&typeByte, sizeof(typeByte));
        if (!file) break;
        ProductType::ProductTypeEnum enumValue = static_cast<ProductType::ProductTypeEnum>(typeByte);
        ProductType type(enumValue);
        Product* product = ProductFactory::create(false, type);
        product->deserialize(file);
        products.push(product);
    }
    file.close();
}

void ProductRepository::save() const {
    std::ofstream file(ProductRepository::PRODUCTS_DATA_FILE_NAME, std::ios::binary | std::ios::trunc);
    if (!file) return;
    size_t length = products.getLength();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    for (size_t i = 0; i < length; ++i) {
        char typeByte = static_cast<char>(static_cast<ProductType::ProductTypeEnum>(products[i]->getType().get()));
        file.write(&typeByte, sizeof(typeByte));
        products[i]->serialize(file);
    }
    file.close();
}

void ProductRepository::free() {
    for (size_t i = 0; i < products.getLength(); i++) {
        delete products[i];
    }
    products.clear();
}