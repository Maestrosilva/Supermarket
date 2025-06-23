#pragma once
#include "..//utils//_Utils.h" 
#include "..//handlers//_Handlers.h"
#include "..//factories//_Factories.h" 
#include "..//repositories//_Repositories.h" 
#include "enums//_Enums.h"
#include "models//_Models.h"
#include <iostream>

class System {
private:
	static CategoryRepository categoryRepository;
	static WorkerRepository workerRepository;
	static ProductRepository productRepository;
	static FeedbackRepository feedbackRepository;
	static TransactionRepository transactionRepository;

	static void reload();

	static void save();

	static void load();

	static void free();

	static void removeCurrent();
	static String getCustomMessage();
	static String createReceipt();

	static void handleRestock(const Vector<String>& args);
	static void handleNewProduct(const Vector<String>& args);

public:
	static Worker* current;
	static Transaction* currentTransaction;
	static String currentUserId;

	System() = delete;

	static void run();

	static void login(const Vector<String> tokens);
	static void registerUser(const Vector<String> tokens);
	static void leave();
	static void logout();

	static void endTransaction();

	static void displayAllWorkers();
	static void displayAllProducts(const String& categoryId = "");
	static void displayAllFeedbacks(size_t limit = 30);
	static void displayAllTransactions();
	static void displayAllCategories();

	static void sell(Product* product, double quantity);

	static void refill(const String& fileName);

	static Worker* getWorkerById(const String& id);
	static Product* getProductById(const String& id);
	static Feedback* getFeedbackById(const String& id);
	static Transaction* getTransactionById(const String& id);
	static Category* getCategoryById(const String& id);

	static void listPending();
	static void listWarnCashiers(size_t minPoints);
	static void removeWorker(Worker* const worker);
	static void addWorker(Worker* const worker);
	static void addCategory(Category* const category);
	static void deleteCategory(Category* const category);
	static void createProduct(const ProductType type, const String& name, const String& categoryId, double price);
	static void deleteProduct(Product* const product);

	static void createFeed(const String& feed);
};