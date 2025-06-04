#include "..//headers//System.h"

Transaction* System::currentTransaction = nullptr;

void System::run() {
    String line;
    while (true) {
        std::cout << "> ";
        std::cin >> line;
        if (line == "exit") {
            break;
        }
        CommandDispatcher::dispatch(line, System::current);
    }
}

void System::login(const Vector<String> tokens) {
    try {
        String id = tokens[0];
        String password = tokens[1];
        Worker* worker = workers.find([](const Worker* w) {
            return w->id == id && w->password == Hasher::hash(password);
            });
        if (worker == nullptr) {
            throw std::invalid_argument("Wrong id or password!");
        }
        current = worker;
    }
    catch (std::out_of_range) {
        throw std::invalid_argument("Invalid format!");
    }
}

void System::registerUser(const Vector<String> tokens) {
    try {
        Role role = Role::getRole(tokens[0]);
        String firstName = tokens[1];
        String lastName = tokens[2];
        String phoneNumber = tokens[3];
        String age = String::toNum(tokens[4]);
        String password = tokens[5];
        Worker* worker = workers.find([](const Worker* w) {
            return w->firstName == firstName && w->lastName == lastName;
            });
        if (worker != nullptr) {
            throw std::invalid_argument("Worker already exists!");
        }
        worker = WorkerFactory::create(role, firstName, lastName, phoneNumber, age, password);
        current = worker;
    }
    catch (std::out_of_range) {
        throw std::invalid_argument("Invalid format!");
    }
}

void System::leave() {
    Feedback feed(current, System::getCustomMessage());
    feedbacks.add(feed);
    removeCurrent();
    save();
    free();
    load();
}

void System::removeCurrent() {
    if (current != nullptr) {
        for (size_t i = 0; i < workers.size(); ++i) {
            if (workers[i] == current) {
                delete workers[i];
                workers[i] = nullptr;
                break;
            }
        }
        current = nullptr;
    }
}

void System::logout() {
    save();
    free();
    load();
    current = nullptr;
}

void System::free() {
    for (size_t i = 0; i < workers.getLength(); i++) {
        delete workers[i];
    }
    workers.clear();

    for (size_t i = 0; i < products.getLength(); i++) {
        delete products[i];
    }
    products.clear();

    for (size_t i = 0; i < feedbacks.getLength(); i++) {
        delete feedbacks[i];
    }
    feedbacks.clear();

    for (size_t i = 0; i < transactions.getLength(); i++) {
        delete transactions[i];
    }
    transactions.clear();
}

void System::emptyFile(const String& fileName) {
    std::ofstream f(fileName, std::ios::trunc);
    f.close();
}

void System::save() {
    WorkerFactory::saveAll(workers, WORKERS_DATA_FILE_NAME);
    ProductFactory::saveAll(products, PRODUCTS_DATA_FILE_NAME);
    FeedbackFactory::saveAll(feedbacks, FEEDBACKS_DATA_FILE_NAME);
    TransactionFactory::saveAll(transactions, TRANSACTIONS_DATA_FILE_NAME);
}

void System::load() {
    free();
    WorkerFactory::populate(workers, WORKERS_DATA_FILE_NAME);
    ProductFactory::populate(products, PRODUCTS_DATA_FILE_NAME);
    FeedbackFactory::populate(feedbacks, FEEDBACKS_DATA_FILE_NAME);
    TransactionFactory::populate(transactions, TRANSACTIONS_DATA_FILE_NAME);
}

String System::getCustomMessage() {
    Vector<String> messages;
    std::ifstream file("..//..//data//no-data.txt");
    if (!file) {
        return "";
    }
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
    String encryptedMessage = messages[index];
    return Hasher::decrypt(encryptedMessage);
}

void System::startTransaction() {
    if (currentTransaction != nullptr) {
        delete currentTransaction;
    }
    currentTransaction = new Transaction(current->getId());
}

void System::endTransaction() {
    if (!currentTransaction) {
        throw std::runtime_error("No active transaction to end!");
    }
    transactions.push(currentTransaction);
    TransactionFactory::saveAll(transactions, TRANSACTIONS_DATA_FILE_NAME);
    std::ofstream receiptFile("receipts.txt", std::ios::app);
    if (!receiptFile) {
        throw std::runtime_error("Failed to open receipts file!");
    }
    receiptFile << currentTransaction->toString() << "\n\n";
    receiptFile.close();
    currentTransaction = nullptr;
}

void System::sell(Product* product, double quantity) {
    if (product->getQuantity() < quantity) {
        throw std::runtime_error("Not enough of this product to sell!");
    }
    product->updateQuantity(-quantity);
    currentTransaction->add({ product, quantity });
}

void System::refill(const String& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        throw std::runtime_error("Failed to open file!");
    }
    String line;
    while (std::getline(file, line)) {
        Vector<String> args = line.split(':');
        if (args.getLength() < 2) continue;
        if (args[0] == "new") {
            products.push(ProductFactory::create(args.subarray(1)));
        }
        else {
            if (args.getLength() < 3) {
                file.close();
                throw std::runtime_error("Invalid product update format.");
            }
            Product* product = System::products.find([&args](const Product* p) {
                return p->getId() == args[1];
                });
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