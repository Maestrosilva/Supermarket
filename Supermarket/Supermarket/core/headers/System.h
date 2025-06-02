#pragma once
#include <iostream>
#include "..//..//handlers//headers//CommandDispatcher.h" 
#include "..//..//utils//headers//Hasher.h" 
#include "..//..//enums//Role.h"
#include "Worker.h"
#include "Product.h"
#include "Feedback.h"
#include "Transaction.h"


class System {
private:
	static void save();
	static void saveWorkers();
	static void saveProducts();
	static void saveFeedbacks();
	static void saveTransactions();

	static void load();
	static void loadWorkers();
	static void loadProducts();
	static void loadFeedbacks();
	static void loadTransactions();

	static void free();
	//static void freeWorkers();
	//static void freeProducts();
	//static void freeFeedbacks();
	//static void freeTransactions();

	static void removeCurrent();
	static const String& getCustomMessage();

	static constexpr String WORKERS_DATA_FILE_NAME = "..//..//data//workers.dat";
	static constexpr String PRODUCTS_DATA_FILE_NAME = "..//..//data//products.dat";
	static constexpr String FEEDBACKS_DATA_FILE_NAME = "..//..//data//feedbacks.dat";
	static constexpr String TRANSACTIONS_DATA_FILE_NAME = "..//..//data//transactions.dat";

public:
	static Worker* current;

	static Vector<Worker*> workers;
	static Vector<Product*> products;
	static Vector<Feedback*> feedbacks;
	static Vector<Transaction*> transactions;

	static void run();

	static void login(const Vector<String> tokens);
	static void registerUser(const Vector<String> tokens);
	static void leave();
	static void logout();
	static void emptyFile(const String& fileName);

	static void sell(const Product* product, double quantity);
	static void refill(const String& fileName);
};