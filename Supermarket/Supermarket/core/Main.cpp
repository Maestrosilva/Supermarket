#include "System.h"

#include <iostream>
#include <fstream>

template <typename T>
void serializeObject(const T* obj, const char* filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Failed to open " << filename << " for writing\n";
        return;
    }
    obj->serialize(ofs);
    ofs.close();
}

template <typename T>
void deserializeObject(T* obj, const char* filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        std::cerr << "Failed to open " << filename << " for reading\n";
        return;
    }
    obj->deserialize(ifs);
    ifs.close();
}

template <typename T>
void testSerialization(T* obj, const char* filename) {
    std::cout << "Original:\n" << obj->toString() << "\n\n";

    serializeObject(obj, filename);

    T* obj2 = new T();
    deserializeObject(obj2, filename);

    std::cout << "Deserialized:\n" << obj2->toString() << "\n\n";
    delete obj2;
}

void tests() {

    // Manager test
    Manager* m = new Manager(String("John"), String("Smith"), String("0888123456"), 35, String("pass123"));
    testSerialization(m, "manager.bin");

    // Cashier test
    Cashier* c = new Cashier(String("Jane"), String("Doe"), String("0888999888"), 28, String("cashierpass"));

    // Create a Warning from the manager to the cashier
    Warning* w = new Warning(m, String("Late to shift"), DegreeOfCriticality::MEDIUM);
    c->addWarning(w);

    testSerialization(c, "cashier.bin");

    // ProductByUnit test
    ProductByUnit* pUnit = new ProductByUnit(String("Cola Can"), String("Drinks"), 1.99, 24);
    testSerialization(pUnit, "product_unit.bin");
    delete pUnit;

    // ProductByWeight test
    ProductByWeight* pWeight = new ProductByWeight(String("Bananas"), String("Fruits"), 2.49, 3.5);
    testSerialization(pWeight, "product_weight.bin");
    delete pWeight;

    // Transaction test
    Transaction* t = new Transaction(c->getId()); // assuming getId() returns String
    t->add(new ProductByUnit(String("Chips"), String("Snacks"), 1.59, 10), 3);
    t->add(new ProductByWeight(String("Apples"), String("Fruits"), 3.99, 2.0), 1.5); // 1.5kg of apples
    t->endTransaction();  // Finalize transaction
    testSerialization(t, "transaction.bin");
    delete t;

    // Feedback test
    Feedback* f = new Feedback(c->getId(), String("Customer was rude and aggressive."));
    testSerialization(f, "feedback.bin");
    delete f;

    // Cleanup
    delete w;
    delete c;
    delete m;
}


int main() {
    System::run();
    //tests();
}

/*
register manager A A 20 20 P
register cashier B B 20 20 B

login 3 P
login 2 B

list-user-data
list-workers
list-products
list-products 1
list-feed
list-transactions
leave
logout

list-pending
*/