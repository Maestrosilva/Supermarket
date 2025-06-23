#include "..//headers//Transaction.h"

const String Transaction::FILE_NAME = "data//receipts//receipt_";

Transaction::Transaction(const String& cashierId)
    : id(String::intToString(IdGenerator::next(IdType::TRANSACTION))),
    cashierId(cashierId), date(Date::getCurrentDate()) {

}

void Transaction::add(const Product* product, double quantity) { 
    if (!product || quantity < 0) {
        std::runtime_error("Invalid Transaction!");
    }
    if (product->getType().get() == ProductType::BY_UNIT && !Math::isWholeNumber(quantity)) {
        throw std::runtime_error("Quantity must be a whole number for unit products.");
    }
    Pair pair = { product->getId(), quantity };
    pairs.push(pair);
    double current = product->getPrice() * pair.quantity;
    total += current;
}

const String& Transaction::getCashierId() const { return cashierId; }

const String& Transaction::getId() const { return id; }

const String& Transaction::getDate() const { return date; }

const Vector<Pair>& Transaction::getPairs() const { return pairs; }

double Transaction::totalPrice() const { return total; }

String Transaction::toString() const {
    return String("Id: ") + id + " | CashierId: " + cashierId + " | Total: " + String::doubleToString(total, 2);
}

void Transaction::endTransaction() {
    ended = true;
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
}