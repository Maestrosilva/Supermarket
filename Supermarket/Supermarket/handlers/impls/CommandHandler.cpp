#include "..//headers//CommandHandler.h"

void CommandHandler::handle(const Vector<String>& tokens) {
	try {
		String command = tokens[0];
		if (command == String("list-user-data")) {
			std::cout << System::current->toString() << std::endl;
		}
		else if (command == String("list-workers")) {
			System::displayAllWorkers();
		}
		else if (command == String("list-products")) {
			System::displayAllProducts();
		}
		else if (command == String("list-feed")) {
			System::displayAllFeedbacks();
		}
		else if (command == String("list-transactions")) {
			System::displayAllTransactions();
		}
		else if (command == String("leave")) {
			System::leave();
		}
		else if (command == String("logout")) {
			System::logout();
		}
	}
	catch (std::exception) {
		throw std::invalid_argument("Something went wrong!");
	}
}