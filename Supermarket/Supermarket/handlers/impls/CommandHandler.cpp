#include "..//headers//CommandHandler.h"

void CommandHandler::handle(const Vector<String> tokens) {
	try {
		String command = tokens[0];
		if (command == "list-user-data") {
			std::cout << System::current->toString();
		}
		else if (command == "list-workers") {
			System::displayAllWorkers();
		}
		else if (command == "list-products") {
			System::displayAllProducts();
		}
		else if (command == "list-feed") {
			System::displayAllFeedbacks();
		}
		else if (command == "list-transactions") {
			System::displayAllTransactions();
		}
		else if (command == "leave") {
			System::leave();
		}
		else if (command == "logout") {
			System::logout();
		}
	}
	catch (std::exception) {
		throw std::invalid_argument("Something went wrong!");
	}
}