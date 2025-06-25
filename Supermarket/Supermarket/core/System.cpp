#include "System.h"

WorkerRepository System::workerRepository;
ProductRepository System::productRepository;
FeedbackRepository System::feedbackRepository;
TransactionRepository System::transactionRepository;
CategoryRepository System::categoryRepository;

Worker* System::current = nullptr;
Transaction* System::currentTransaction = nullptr;
String System::currentUserId = "-1";

void System::reload() {
    IdGenerator::reload();
    save();
    free();
    load();
    if (currentUserId != String("-1")) {
        current = workerRepository.getById(currentUserId);
    }
}

void System::save() {
    workerRepository.save();
    productRepository.save();
    feedbackRepository.save();
    transactionRepository.save();
    categoryRepository.save();
}

void System::load() {
    workerRepository.load();
    productRepository.load();
    feedbackRepository.load();
    transactionRepository.load();
    categoryRepository.load();
}

void System::free() {
    String savedUserId = currentUserId;
    workerRepository.free();
    productRepository.free();
    feedbackRepository.free();
    transactionRepository.free();
    categoryRepository.free();
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
    std::ifstream file("data//no-data.txt");
    if (!file) return "";
    String line;
    while (readLine(file, line)) {
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
    receipt.append("<----------------------------->\n");
    Vector<Pair> pairs = currentTransaction->getPairs();
    for (size_t i = 0; i < pairs.getLength(); i++) {
        Product* product = productRepository.getById(pairs[i].productId);
        receipt.append(product->getName()).append("\n");
        double price = product->getPrice();
        switch (product->getType().get()) {
        case ProductType::BY_UNIT: receipt.append(String::intToString(pairs[i].quantity));
            break;
        case ProductType::BY_WEIGHT: receipt.append(String::doubleToString(pairs[i].quantity, 3));
            break;
        default: throw std::runtime_error("Invalid type!");
        }
        receipt.append("*").append(String::doubleToString(price, 2)).append(" - ");
        receipt.append(String::doubleToString(price * pairs[i].quantity, 2).append("\n"));
        receipt.append("\n").append("###").append("\n\n");
    }
    receipt.append(currentTransaction->getDate()).append("\n");
    receipt.append("Total: ").append(String::doubleToString(currentTransaction->totalPrice(), 2));
    return receipt;
}

void System::handleRestock(const Vector<String>& args) {
    if (args.getLength() < 2) {
        throw std::runtime_error("Invalid format for restock!");
    }
    String name = args[0];
    Product* product = productRepository.getByName(name);
    if (!product) {
        throw std::runtime_error("Product not found: " + name);
    }
    double quantity = String::toDouble(args[1]);
    if (product->getType() == ProductType::BY_UNIT) {
        quantity = static_cast<size_t>(quantity);
    }
    product->updateQuantity(quantity);
}

void System::handleNewProduct(const Vector<String>& args) {
    if (args.getLength() < 6) return;
    ProductType type = ProductType::get(args[1]);
    String name = args[2];
    Category* category = categoryRepository.getByName(args[3]);
    if (!category) {
        category = new Category(args[3], "");
        addCategory(category);
    }
    double price = String::toDouble(args[4]);
    double quantity = String::toDouble(args[5]);
    if (type == ProductType::BY_UNIT) {
        quantity = static_cast<size_t>(quantity);
    }
    createProduct(type, name, category->getId(), price);
    if (Product* product = productRepository.getByName(name)) {
        product->updateQuantity(quantity);
    }
}

void System::refill(const String& fileName) {
    std::ifstream file(fileName);
    if (!file) throw std::runtime_error("Failed to open file!");
    String line;
    while (file >> line) {
        try {
            Vector<String> args = line.split(':');
            if (args.getLength() < 2) continue;
            if (args[0] == String("new")) {
                handleNewProduct(args);
            }
            else {
                handleRestock(args);
            }
        }
        catch (std::exception) {
            continue;
        }
    }
    String feed = "Products loaded from: " + fileName;
    std::cout << feed << std::endl;
    createFeed(feed);
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
    file << createReceipt();
    file.close();
    String feed = String("Transaction with id ") + currentTransaction->getId() + String(" ended!");
    std::cout << feed << std::endl;
    std::cout << "Receipt seved as: " << fileName << std::endl;
    std::cout << "Total: " << currentTransaction->totalPrice() << std::endl;
    createFeed(feed);
    currentTransaction = nullptr;
}

void System::displayAllWorkers() {
    workerRepository.getWorkers().foreach([](const Worker* w) {std::cout << w->toString() << std::endl; });
}

void System::displayAllProducts(const String& categoryId) {
    unsigned short number = 0;
    if (categoryId == String("")) {
        productRepository.getProducts()
            .foreach([&](const Product* p) { std::cout << p->getId() << ". " << p->toString() 
                << " - " << categoryRepository.getById(p->getCategoryId())->getName() << std::endl; });
    }
    else {
        productRepository.getProducts()
            .filtered([&](const Product* p) { return p->getCategoryId() == categoryId; })
            .foreach([&](const Product* p) { std::cout << p->getId() << ". " << p->toString()
                << " - " << categoryRepository.getById(p->getCategoryId())->getName() << std::endl; });
    }
}

void System::displayAllFeedbacks(size_t limit) {
    feedbackRepository.getFeedbacks().reversed()
        .foreach([&](const Feedback* f) {
        if (limit--) { std::cout << f->toString() << std::endl; }});
}

void System::displayAllTransactions() {
    transactionRepository.getTransactions()
        .foreach([](const Transaction* t) {std::cout << t->toString() << std::endl; });
}

void System::displayAllCategories() {
    unsigned short number = 0;
    categoryRepository.getCategories()
        .foreach([&](const Category* c) {std::cout << ++number << ". " << c->toString() << std::endl; });
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

Category* System::getCategoryById(const String& id) {
    return categoryRepository.getById(id);
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
    if (!worker) {
        throw std::runtime_error("Worker with this id does not exist!");
    }
    workerRepository.remove(worker);
}

void System::addWorker(Worker* const worker) {
    if (workerRepository.getByName(worker->getFirstName(), worker->getLastName())) {
        IdGenerator::rollback(IdType::WORKER);
        throw std::runtime_error("Worker with this name already exist!");
    }
    workerRepository.add(worker);
}

void System::addCategory(Category* const category) {
    if (categoryRepository.getByName(category->getName())) {
        IdGenerator::rollback(IdType::PRODUCT);
        throw std::runtime_error("Category with this name already exists!");
    }
    categoryRepository.add(category);
}

void System::deleteCategory(Category* const category) {
    if (!category) {
        throw std::runtime_error("Category with this id does not exist!");
    }
    if (!productRepository.getByCategoryId(category->getId()).isEmpty()) {
        throw std::runtime_error("Products with this category still exist!");
    }
    categoryRepository.remove(category);
}

void System::createProduct(const ProductType type, const String& name, const String& categoryId, double price) {
    if (!categoryRepository.getById(categoryId)) {
        throw std::runtime_error("Category with this id doesn't exist!");
    }
    if (price < 0) {
        throw std::runtime_error("Price cannot be negative!");
    }
    if (productRepository.getByName(name)) {
        throw std::runtime_error("Product with this name already exists!");
    }
    Product* p = ProductFactory::create(true, type, name, categoryId, price);
    productRepository.add(p);
}

void System::deleteProduct(Product* const product) {
    if (!product) {
        throw std::runtime_error("Product with this id does not exist!");
    }
    productRepository.remove(product);
}

void System::createFeed(const String& feed) {
    feedbackRepository.add(new Feedback(currentUserId, feed));
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
    Validator::validateName(tokens[1]);
    Validator::validateName(tokens[2]);
    Validator::validatePhoneNumber(tokens[3]);
    Validator::validateAge(String::toInt(tokens[4]));
    Validator::validatePassword(tokens[5]);
    Role role = Role::get(tokens[0]);
    Worker* w = WorkerFactory::create(true, role, tokens[1], tokens[2], tokens[3], String::toInt(tokens[4]), tokens[5]);
    addWorker(w);
    std::cout << "Successful registration!" << std::endl;
    if (role == Role::CASHIER) {
        std::cout << "Pending for approval from a manager!" << std::endl;
        return;
    }
    current = w;
    currentUserId = w->getId();
    createFeed(String("Worker with id ") + currentUserId + String("registered!"));
}

void System::leave() {
    createFeed(String("Worker with id ") + currentUserId + String("left!"));
    removeCurrent();
    save();
    std::cout << getCustomMessage() << std::endl;
}

void System::logout() {
    current = nullptr;
    currentUserId = "-1";
    delete currentTransaction;
    currentTransaction = nullptr;
}

void System::run() {
    load();
    std::cout << "Welcome to Supermarket System!" << std::endl;
    String line;
    while (true) {
        std::cout << "> ";
        readLine(std::cin, line);
        if (line == String("exit")) break;
        CommandDispatcher::dispatch(line, current);
        reload();
        std::cout << std::endl;
    }
    free();
    delete current;
}