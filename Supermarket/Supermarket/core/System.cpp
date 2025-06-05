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

void System::save() {
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
        workerRepository.remove(current);
        delete current;
        current = nullptr;
    }
}

String System::getCustomMessage() {
    Vector<String> messages;
    std::ifstream file("..//..//data//no-data.txt");
    if (!file) return "";
    String line;
    while (file >> line) {
        messages.push(line);
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
    while (file >> line) {
        Vector<String> args = line.split(':');
        if (args.getLength() < 2) continue;
        if (args[0] == String("new")) {
            ProductType pt = ProductType::get(args[1]);
            String name = args[2];
            String categoryName = args[3];
            ProductType pt = ProductType::get(args[1]);
            Product* p = ProductFactory::create(pt);
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

void System::endTransaction() {
    if (!currentTransaction) {
        throw std::runtime_error("No active transaction to end!");
    }
    currentTransaction->endTransaction();
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

void System::displayAllWorkers() {
    workerRepository.getWorkers().foreach([](const Worker* w) {std::cout << w->toString() << std::endl; });
}

void System::displayAllProducts(const String& categoryId) {
    if (categoryId == String("")) {
        productRepository.getProducts().foreach([](const Product* p) {std::cout << p->toString() << std::endl; });
    }
    else {
        productRepository.getProducts().filtered([&](const Product* p) {return p->getCategoryId() == categoryId; }).foreach([](const Product* p) {std::cout << p->toString() << std::endl; });
    }
}

void System::displayAllFeedbacks() {
    feedbackRepository.getFeedbacks().foreach([](const Feedback* f) {std::cout << f->toString() << std::endl; });
}

void System::displayAllTransactions() {
    transactionRepository.getTransactions().foreach([](const Transaction* t) {std::cout << t->getCashierId() << " " << t->totalPrice() << "lv." << std::endl; });
}

void System::sell(Product* product, double quantity) {
    if (!currentTransaction) {
        currentTransaction = new Transaction(current->getId());
    }
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
    Role role = Role::get(tokens[0]);
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
    String line;
    while (true) {
        reload();
        std::cout << "> ";
        std::cin >> line;
        if (line == String("exit")) break;
        CommandDispatcher::dispatch(line, current);
    }
}