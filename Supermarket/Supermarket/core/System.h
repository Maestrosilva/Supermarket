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

public:
	static Worker* current;
	static Transaction* currentTransaction;

	System() = delete;

	static void run();

	static void login(const Vector<String> tokens);
	static void registerUser(const Vector<String> tokens);
	static void leave();
	static void logout();

	static void endTransaction();

	static void displayAllWorkers();
	static void displayAllProducts(const String& categoryId = "");
	static void displayAllFeedbacks();
	static void displayAllTransactions();

	static void sell(Product* product, double quantity);

	static void refill(const String& fileName);

	static Worker* getWorkerById(const String& id);
	static Product* getProductById(const String& id);
	static Feedback* getFeedbackById(const String& id);
	static Transaction* getTransactionById(const String& id);
};