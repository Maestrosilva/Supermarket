#include "..//headers//TransactionRepository.h"

Vector<Transaction*> TransactionRepository::transactions;

const Vector<Transaction*>& TransactionRepository::getTransaction() { return transactions; }

const Transaction* TransactionRepository::getById(const String& id) {
    for (size_t i = 0; i < transactions.getLength(); ++i) {
        if (transactions[i]->getId() == id) {
            return transactions[i];
        }
    }
    return nullptr;
}

void TransactionRepository::add(Transaction* transaction) { transactions.push(transaction); }
void TransactionRepository::remove(const Transaction* transaction) { transactions.remove(transaction); }

void TransactionRepository::load() {
    free();
    std::ifstream file(TRANSACTIONS_DATA_FILE_NAME, std::ios::binary);
    if (!file) return;
    size_t length = 0;
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    for (size_t i = 0; i < length; ++i) {
        Transaction* transaction = new Transaction();
        transaction->deserialize(file);
        transactions.push(transaction);
    }
    file.close();
}

void TransactionRepository::save() const {
    std::ofstream file(TRANSACTIONS_DATA_FILE_NAME, std::ios::binary | std::ios::trunc);
    if (!file) {
        throw std::runtime_error("Failed to open transactions file!");
    }
    size_t length = transactions.getLength();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    for (size_t i = 0; i < length; ++i) {
        transactions[i]->serialize(file);
    }
    file.close();
}

void TransactionRepository::free() {
    for (size_t i = 0; i < transactions.getLength(); ++i) {
        delete transactions[i];
    }
    transactions.clear();
}