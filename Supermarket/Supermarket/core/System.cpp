#include "System.h"

WorkerRepository System::workerRepository;
ProductRepository System::productRepository;
FeedbackRepository System::feedbackRepository;
TransactionRepository System::transactionRepository;

Worker* System::current = nullptr;
Transaction* System::currentTransaction = nullptr;

void System::reload() {
    workerRepository.reload();
    productRepository.reload();
    feedbackRepository.reload();
    transactionRepository.reload();
}

void System::save() const {
    workerRepository.save();
    productRepository.save();
    feedbackRepository.save();
    transactionRepository.save();
}

void System::load() {
    workerRepository.load();
    productRepository.load();
    feedbackRepository.load();
    transactionRepository.load();
}

void System::free() {
    workerRepository.free();
    productRepository.free();
    feedbackRepository.free();
    transactionRepository.free();
    delete current;
    current = nullptr;
    delete currentTransaction;
    currentTransaction = nullptr;
}

void System::removeCurrent() {
    if (current) {
        workerRepository.remove(current->getId());
        delete current;
        current = nullptr;
    }
}

String System::getCustomMessage() {
    Vector<String> messages;
    std::ifstream file("..//..//data//no-data.txt");
    if (!file) return "";
    String line;
    while (std::getline(file, line)) {
        if (line.getSize() > 0) {
            messages.push(line);
        }
    }
    file.close();
    static bool seeded = false;
    if (!seeded) {
        std::srand(std::time(nullptr));
        seeded = true;
    }
    size_t index = std::rand() % messages.getLength();
    return Hasher::decrypt(messages[index]);
}

void System::refill(const String& fileName) {
    std::ifstream file(fileName);
    if (!file) throw std::runtime_error("Failed to open file!");
    String line;
    while (std::getline(file, line)) {
        Vector<String> args = line.split(':');
        if (args.getLength() < 2) continue;
        if (args[0] == "new") {
            Product* p = ProductFactory::create(args.subarray(1));
            productRepository.add(p);
        }
        else {
            if (args.getLength() < 3) {
                file.close();
                throw std::runtime_error("Invalid format!");
            }
            Product* product = productRepository.getById(args[1]);
            if (!product) {
                file.close();
                throw std::runtime_error("Product not found with ID: " + args[1]);
            }
            double quantity = String::toDouble(args[2]);
            if (product->getType() == ProductType::BY_UNIT) {
                quantity = static_cast<size_t>(quantity);
            }
            product->updateQuantity(quantity);
        }
    }
    file.close();
}

void System::startTransaction() {
    delete currentTransaction;
    currentTransaction = new Transaction(current->getId());
}

void System::endTransaction() {
    if (!currentTransaction) {
        throw std::runtime_error("No active transaction to end!");
    }
    transactionRepository.add(currentTransaction);
    transactionRepository.save();
    String fileName = Transaction::FILE_NAME + currentTransaction->getId() + ".txt";
    std::ofstream file(fileName);
    if (!file) {
        throw std::runtime_error("Failed to open receipt file: " + fileName);
    }
    file << currentTransaction->toString() << "\n\n";
    file.close();
    currentTransaction = nullptr;
}

void System::sell(Product* product, double quantity) {
    if (product->getQuantity() < quantity) {
        throw std::runtime_error("Not enough of this product to sell!");
    }
    product->updateQuantity(-quantity);
    currentTransaction->add({ product->getId(), quantity });
}

void System::login(const Vector<String> tokens) {
    if (tokens.getLength() < 2) {
        throw std::runtime_error("Invalid login format!");
    }
    Worker* found = workerRepository.getByIdAndPass(tokens[0], tokens[1]);
    if (!found) {
        throw std::runtime_error("Invalid Id or password.");
    }
    current = found;
}

void System::registerUser(const Vector<String> tokens) {
    if (tokens.getLength() < 6) {
        throw std::runtime_error("Invalid format!");
    }
    Role role = Role::fromString(tokens[0]);
    Worker* w = WorkerFactory::create(role, tokens[1], tokens[2], tokens[3], (unsigned char)String::toInt(tokens[4]), tokens[5]);
    workerRepository.add(w);
    workerRepository.save();
}

void System::leave() {
    removeCurrent();
    save();
}

void System::logout() {
    current = nullptr;
    delete currentTransaction;
    currentTransaction = nullptr;
}

void System::run() {
    load();
    String line;
    while (true) {
        std::cout << "> ";
        std::cin >> line;
        if (line == "exit") break;
        CommandDispatcher::dispatch(line, current);
    }
    save();
    free();
}