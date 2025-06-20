#include "System.h"

WorkerRepository System::workerRepository;
ProductRepository System::productRepository;
FeedbackRepository System::feedbackRepository;
TransactionRepository System::transactionRepository;

Worker* System::current = nullptr;
Transaction* System::currentTransaction = nullptr;
String System::currentUserId = "-1";

void System::reload() {
    workerRepository.reload();
    productRepository.reload();
    feedbackRepository.reload();
    transactionRepository.reload();
    if (currentUserId != String("-1")) {
        current = workerRepository.getById(currentUserId);
    }
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
    if (currentUserId != String("-1")) {
        current = workerRepository.getById(currentUserId);
    }
}

void System::free() {
    String savedUserId = currentUserId;
    workerRepository.free();
    productRepository.free();
    feedbackRepository.free();
    transactionRepository.free();
    delete current;
    current = nullptr;
    delete currentTransaction;
    currentTransaction = nullptr;
    if (savedUserId != String("-1")) {
        currentUserId = savedUserId;
        current = nullptr;
    }
    else {
        currentUserId = "-1";
        current = nullptr;
    }
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

String System::createReceipt() {
    String receipt;
    receipt.append("RECEIPT\n");
    receipt.append("TRANSACTION_ID: ").append(currentTransaction->getId()).append("\n");
    receipt.append("CASHIER_ID: ").append(currentTransaction->getCashierId()).append("\n");
    receipt.append(currentTransaction->getDate()).append("\n");
    receipt.append("<----------------------------->\n");
    Vector<Pair> pairs = currentTransaction->getPairs();
    for (size_t i = 0; i < pairs.getLength(); i++) {
        Product* product = productRepository.getById(pairs[i].productId);
        double price = product->getPrice();
        switch (product->getType().get()) {
            std::cout << product->getName() << std::endl;
        case ProductType::BY_UNIT: receipt.append(String::intToString(pairs[i].quantity));
        case ProductType::BY_WEIGHT: receipt.append(String::doubleToString(pairs[i].quantity, 3));
        default: throw std::runtime_error("Invalid type!");
        }
        receipt.append("*").append(String::doubleToString(price, 2)).append(" - ");
        receipt.append(String::doubleToString(price * pairs[i].quantity, 2).append("\n"));
        receipt.append("###").append("\n");
    }
    receipt.append("Total: ").append(currentTransaction->totalPrice()).append("\n");
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
            Product* p = ProductFactory::create(true, pt);
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
    currentTransaction->add(product, quantity);
}

Worker* System::getWorkerById(const String& id) {
    return workerRepository.getById(id);
}

Product* System::getProductById(const String& id) {
    return productRepository.getById(id);
}
Feedback* System::getFeedbackById(const String& id) {
    return feedbackRepository.getById(id);
}
Transaction* System::getTransactionById(const String& id) {
    return transactionRepository.getById(id);
}

void System::listPending() {
    Vector<Cashier*> cashiers = workerRepository.getWorkers()
        .filtered([](const Worker* w) { return w->getRole() == Role::CASHIER; })
        .mapped<Cashier*>([](Worker* worker) { return dynamic_cast<Cashier*>(worker); })
        .filtered([](const Cashier* c) { return c && !c->isApproved(); });
    cashiers.foreach([](const Cashier* c) { std::cout << c->toString() << std::endl; });
    if (cashiers.isEmpty()) {
        std::cout << "No pending cashiers!" << std::endl;
    }

}

void System::listWarnCashiers(size_t minPoints) {
    Vector<Cashier*> cashiers = workerRepository.getWorkers()
        .filtered([](const Worker* w) { return w->getRole() == Role::CASHIER; })
        .mapped<Cashier*>([](Worker* worker) { return dynamic_cast<Cashier*>(worker); })
        .filtered([&](const Cashier* c) {
        size_t points = 0;
        c->getWarnings()
            .foreach([&](const Warning* w) { points += static_cast<size_t>(w->getDegreeOfCriticality()); });
        return points >= minPoints;
            });
    cashiers.foreach([](const Cashier* c) { std::cout << c->toString() << std::endl; });
    if (cashiers.isEmpty()) {
        std::cout << "No pending cashiers!" << std::endl;
    }
}

void System::removeWorker(Worker* const worker) {
    workerRepository.remove(worker);
}

void System::addWorker(Worker* worker) {
    workerRepository.add(worker);
}

void System::login(const Vector<String> tokens) {
    if (tokens.getLength() < 2) {
        throw std::runtime_error("Invalid login format!");
    }
    Worker* found = workerRepository.getByIdAndPass(tokens[0], tokens[1]);
    if (!found) {
        throw std::runtime_error("Invalid Id or password!");
    }
    Cashier* cashier = dynamic_cast<Cashier*>(found);
    if (cashier && !cashier->isApproved()) {
        throw std::runtime_error("Cashier not approved by a manager!");
    }
    current = found;
    currentUserId = found->getId();
    std::cout << "Worker " << found->getFirstName() << " " << found->getLastName() << " with id: " 
        << found->getId() << " has been logged!" << std::endl;
}

void System::registerUser(const Vector<String> tokens) {
    if (tokens.getLength() < 6) {
        throw std::runtime_error("Invalid format!");
    }
    Role role = Role::get(tokens[0]);
    Worker* w = WorkerFactory::create(true, role, tokens[1], tokens[2], tokens[3], (unsigned char)String::toInt(tokens[4]), tokens[5]);
    workerRepository.add(w);
    workerRepository.save();
    std::cout << "Successful registration!" << std::endl;
    if (role == Role::CASHIER) {
        std::cout << "Pending for approval from a manager!" << std::endl;
        return;
    }
    current = w;
    currentUserId = w->getId();
}

void System::leave() {
    removeCurrent();
    save();
}

void System::logout() {
    current = nullptr;
    currentUserId = "-1";
    delete currentTransaction;
    currentTransaction = nullptr;
}

void System::run() {
    load();
    String line;
    while (true) {
        std::cout << "> ";
        readLine(std::cin, line);
        if (line == String("exit")) break;
        CommandDispatcher::dispatch(line, current);
        reload();
        std::cout << std::endl;
    }
    save();
}