#include "..//headers//Transaction.h"

const String Transaction::FILE_NAME = "..//..//receipts//receipt_";

Transaction::Transaction(const String& cashierId)
    : id(String::intToString(IdGenerator::next(IdType::TRANSACTION))),
    cashierId(cashierId), date(Date::getCurrentDate()) {
    receipt.append("RECEIPT\n");
    receipt.append("TRANSACTION_ID: ").append(id).append("\n");
    receipt.append("CASHIER_ID: ").append(cashierId).append("\n");
    receipt.append(date).append("\n");
    receipt.append("<----------------------------->\n");
}

void Transaction::add(const Pair& pair) { 
    pairs.push(pair);
    Product* product = System::getProductById(pair.productId);
    double current = product->getPrice() * pair.quantity;;
    receipt.append(product->getName()).append("\n");
    receipt.append(product->getPrice()).append("*");
    switch (product->getType().get()) {
    case ProductType::BY_UNIT: receipt.append(String::intToString(pair.quantity));
    case ProductType::BY_WEIGHT: receipt.append(String::doubleToString(pair.quantity, 3));
    default: throw std::runtime_error("Invalid type!");
    }
    receipt.append(" - ").append(String::doubleToString(current, 2));
    receipt.append("###\n");
    total += current;
}

const String& Transaction::getCashierId() const { return cashierId; }
const String& Transaction::getId() const { return id; }

double Transaction::totalPrice() const { return total; }

String Transaction::toString() const { return receipt; }

void Transaction::endTransaction() {
    ended = true;
    receipt.append("TOTAL: ").append(String::doubleToString(totalPrice(), 2)).append("\n");
    std::ofstream receiptFile(Transaction::FILE_NAME + id + ".txt");
    if (!receiptFile) {
        throw std::runtime_error("Failed to open receipt file for writing.");
    }
    receiptFile << receipt;
    receiptFile.close();
}

void Transaction::serialize(std::ostream& os) const {
    id.serialize(os);
    cashierId.serialize(os);
    date.serialize(os);
    size_t count = pairs.getLength();
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (size_t i = 0; i < count; ++i) {
        pairs[i].productId.serialize(os);
        os.write(reinterpret_cast<const char*>(&pairs[i].quantity), sizeof(pairs[i].quantity));
    }
    os.write(reinterpret_cast<const char*>(&ended), sizeof(ended));
    os.write(reinterpret_cast<const char*>(&total), sizeof(total));
    receipt.serialize(os);
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
        p.productId.deserialize(is);
        is.read(reinterpret_cast<char*>(&p.quantity), sizeof(p.quantity));
        pairs.push(p);
    }
    is.read(reinterpret_cast<char*>(&ended), sizeof(ended));
    is.read(reinterpret_cast<char*>(&total), sizeof(total));
    receipt.deserialize(is);
}