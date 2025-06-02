#include "..//headers//CommandHandler.h"

void CommandHandler::handle(const Vector<String> tokens) {
	try {
		String command = tokens[0];
		else if (command == "list-user-data") {
			std::cout << System::current->toString();
		}
		else if (command == "list-workers") {
			System::workers.foreach([](const Worker& w) { std::cout << w.toString() << std::endl; });
		}
		else if (command == "list-products") {
			System::products.foreach([](const Product& p) { std::cout << p.toString() << std:endl; });
		}
		else if (command == "list-feed") {
			System::feedbacks.foreach([](const Feedback& f) { std::cout << f.toString() << std:endl; });
		}
		else if (command == "list-transactions") {
			System::transactions.foreach([](const Transaction& t) { std::cout << t.toString() << std:endl; });
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