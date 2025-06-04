#include "..//headers//Transaction.h"
#include "..//headers//ProductFactory.h"
#include "..//utils//headers//Date.h"
#include "..//utils//headers//IdGenerator.h"

Transaction::Transaction(const String& cashierId)
    : id(String::intToString(IdGenerator::next(IdType::TRANSACTION))), cashierId(cashierId), date(Date::getCurrentDate()) {}

void Transaction::add(const Pair& pair) { pairs.push(pair); }

String Transaction::toString() const {
    String toReturn;
    toReturn.append("RECEIPT\n");
    toReturn.append("TRANSACTION_ID: ").append(id).append("\n");
    toReturn.append("CASHIER_ID: ").append(cashierId).append("\n");
    toReturn.append(date).append("\n");
    toReturn.append("<----------------------------->\n");
    double totalPrice = 0;
    for (size_t i = 0; i < pairs.getLength(); i++) {
        toReturn.append(pairs[i].product->getName()).append("\n");
        double currentPrice = pairs[i].quantity * pairs[i].product->getPrice();
        totalPrice += currentPrice;
        toReturn.append(String::doubleToString(pairs[i].quantity, 2)).append("*")
            .append(String::doubleToString(pairs[i].product->getPrice(), 2))
            .append(" - ")
            .append(String::doubleToString(currentPrice, 2))
            .append("\n###\n");
    }
    toReturn.append("TOTAL_PRICE: ").append(String::doubleToString(totalPrice, 2)).append("\n");
    return toReturn;
}

void Pair::serialize(std::ostream& os) const {
    char typeByte = static_cast<char>(product->getType().getType());
    os.write(&typeByte, sizeof(typeByte));
    product->getName().serialize(os);
    product->getCategory().serialize(os);
    double price = product->getPrice();
    os.write(reinterpret_cast<const char*>(&price), sizeof(price));
    double quantityOrWeight = 0.0;
    if (typeByte == static_cast<char>(ProductType::BY_UNIT)) {
        quantityOrWeight = static_cast<double>(static_cast<ProductsByUnit*>(product)->getQuantity());
    }
    else if (typeByte == static_cast<char>(ProductType::BY_WEIGHT)) {
        quantityOrWeight = static_cast<ProductsByWeight*>(product)->getQuantity();
    }
    os.write(reinterpret_cast<const char*>(&quantityOrWeight), sizeof(quantityOrWeight));
    os.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));
}

void Pair::deserialize(std::istream& is) {
    char typeByte;
    is.read(&typeByte, sizeof(typeByte));
    ProductType::Type type = static_cast<ProductType::Type>(typeByte);
    String name;
    name.deserialize(is);
    Category category;
    category.deserialize(is);
    double price;
    is.read(reinterpret_cast<char*>(&price), sizeof(price));
    double quantityOrWeight;
    is.read(reinterpret_cast<char*>(&quantityOrWeight), sizeof(quantityOrWeight));
    product = ProductFactory::create(type, name, category, price, quantityOrWeight);
    is.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));
}

void Transaction::serialize(std::ostream& os) const {
    id.serialize(os);
    cashierId.serialize(os);
    date.serialize(os);
    size_t count = pairs.getLength();
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (size_t i = 0; i < count; ++i) {
        pairs[i].serialize(os);
    }
    os.write(reinterpret_cast<const char*>(&ended), sizeof(ended));
}
void Transaction::deserialize(std::istream& is) {
    id.deserialize(is);
    cashierId.deserialize(is);
    date.deserialize(is);
    size_t count = 0;
    is.read(reinterpret_cast<char*>(&count), sizeof(count));
    pairs.clear();
    for (size_t i = 0; i < count; ++i) {
        Pair p;
        p.deserialize(is);
        pairs.push(p);
    }
    is.read(reinterpret_cast<char*>(&ended), sizeof(ended));
}

Transaction::~Transaction() {
    for (size_t i = 0; i < pairs.getLength(); i++) {
        delete pairs[i].product;
    }
}