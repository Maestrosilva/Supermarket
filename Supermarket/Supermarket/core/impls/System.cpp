#include "..//headers//System.h" 

void System::run() {
    String line;
    while (true) {
        std::cout << "> ";
        std::cin >> line;
        if (line == "exit") {
            break;
        }
        Worker* user = CommandDispatcher::dispatch(line, System::current);
    }
}

void System::login(const Vector<String> tokens) {
    try {
        String id = tokens[0];
        String password = tokens[1];
        Worker* worker = workers.find([](const Worker* w) { return w->id == id && w->password == password; });
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
        Worker* worker = workers.find([](const Worker* w) { return w->firstName == firstName && w->lastName == lastName; });
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
    for (size_t i = 0; i < products.getLength(); i++) {
        delete products[i];
    }
    for (size_t i = 0; i < feedbacks.getLength(); i++) {
        delete feedbacks[i];
    }
    for (size_t i = 0; i < transactions.getLength(); i++) {
        delete transactions[i];
    }
}

void System::emptyFile(const String& fileName) {
    std::ofstream f(WORKERS_DATA_FILE_NAME, std::ios::truc);
    f.close();
}

void System::save() {
    saveWorkers();
    saveProducts();
    saveFeedbacks();
    //saveTransactions();
}

void System::saveWorkers() {
    emptyFile(WORKERS_DATA_FILE_NAME);
    std::ofstream workersFile(WORKERS_DATA_FILE_NAME, std::ios::binary);
    if (!workersFile) { return; }
    workersFile.write((char*)&workers.getLength(), sizeof(workers.getLength()));
    for (size_t i = 0; i < workers.getLength(); i++) {
        workers[i]->serialize(workersFile);
    }
    workersFile.close();
}

void System::saveProducts() {
    emptyFile(PRODUCTS_DATA_FILE_NAME);
    std::ofstream productsFile(PRODUCTS_DATA_FILE_NAME, std::ios::binary);
    if (!productsFile) { return; }
    productsFile.write((char*)&products.getLength(), sizeof(products.getLength()));
    for (size_t i = 0; i < products.getLength(); i++) {
        products[i]->serialize(productsFile);
    }
    productsFile.close();
}

void System::saveFeedbacks() {
    emptyFile(FEEDBACKS_DATA_FILE_NAME);
    std::ofstream feedbacksFile(FEEDBACKS_DATA_FILE_NAME, std::ios::binary);
    if (!feedbacksFile) { return; }
    feedbacksFile.write((char*)&feedbacks.getLength(), sizeof(feedbacks.getLength()));
    for (size_t i = 0; i < feedbacks.getLength(); i++) {
        feedbacks[i]->serialize(feedbacksFile);
    }
    feedbacksFile.close();
}

void System::saveTransactions() {
    emptyFile(TRANSACTIONS_DATA_FILE_NAME);
    std::ofstream transactionsFile(TRANSACTIONS_DATA_FILE_NAME, std::ios::binary);
    if (!transactionsFile) { return; }
    transactionsFile.write((char*)&transactions.getLength(), sizeof(transactions.getLength()));
    for (size_t i = 0; i < transactions.getLength(); i++) {
        transactions[i]->serialize(transactionsFile);
    }
    transactionsFile.close();
}

void System::load() {
    loadWorkers();
    loadProducts();
    loadFeedbacks();
    loadTransactions();
}

void System::loadWorkers() {
    std::ifstream workersFile(WORKERS_DATA_FILE_NAME, std::ios::binary);
    if (!workersFile) { return; }
    size_t count = 0;
    workersFile.read((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; ++i) {
        Worker* worker = new Worker();
        worker->deserialize(workersFile);
        workers.push(worker);
    }
    workersFile.close();
}

void System::loadProducts() {
    std::ifstream productsFile(PRODUCTS_DATA_FILE_NAME, std::ios::binary);
    if (!productsFile) { return; }
    size_t count = 0;
    productsFile.read((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; ++i) {
        Product* product = new Product();
        product->deserialize(productsFile);
        products.push(product);
    }
    productsFile.close();
}

void System::loadFeedbacks() {
    std::ifstream feedbacksFile(FEEDBACKS_DATA_FILE_NAME, std::ios::binary);
    if (!feedbacksFile) { return; }
    size_t count = 0;
    feedbacksFile.read((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; ++i) {
        Feedback* feedback = new Feedback();
        feedback->deserialize(feedbacksFile);
        feedbacks.push(feedback);
    }
    feedbacksFile.close();
}

void System::loadTransactions() {
    std::ifstream transactionsFile(TRANSACTIONS_DATA_FILE_NAME, std::ios::binary);
    if (!transactionsFile) { return; }
    size_t count = 0;
    transactionsFile.read((char*)&count, sizeof(count));
    for (size_t i = 0; i < count; ++i) {
        Transaction* transaction = new Transaction();
        transaction->deserialize(transactionsFile);
        transactions.push(transaction);
    }
    transactionsFile.close();
}

const String& System::getCustomMessage() {
    Vector<String> messages;
    std::ifstream file("..//..//data//no-data.txt");
    if (!file) {
        return "";
    }
    String line;
    while (file.good()) {
        std::getline(file, line);
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

void System::sell(const Product* product, double quantity) {
    if (product->getQuantity() < quantity) {
        throw std::runtime_error("Not enough of this product to sell!");
    }
    product->updateQuantity(-quantity);
}

void System::refill(const String& fileName) {
    std::ifstream file(fileName.c_str());
    if (!file) throw std::runtime_error("Failed to open refill file!");
    String line;
    while (std::getline(file, line)) {
        Vector<String> args = line.split(':');
        if (args.getLength() < 2) continue;
        if (args[0] == "new") {
            try {
                products.push(ProductFactory::create(args.subarray(1)));
            }
            catch (const std::exception&) {
                file.close();
                throw std::runtime_error("Only products with integer quantity can be created!");
            }
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
            try {
                product->updateQuantity(String::toNum(args[2]));
            }
            catch (const std::exception&) {
                file.close();
                throw std::runtime_error("Only integer quantity can be added to a product!");
            }
        }
    }
    file.close();
}