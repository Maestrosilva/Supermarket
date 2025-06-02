#include "..//headers//CommandDispatcher.h"

void CommandDispatcher::dispatch(const String& line, const Worker* current) {
	try {
		Vector<String> tokens = line.split(' ');
		if (tokens.isEmpty()) throw std::invalid_argument("Empty command!");
		String command = tokens[0];
		if (current == nullptr) {
			if (command == "login") {
				System::login(tokens.subarray(1));
			}
			if (command == "register") {
				System::registerUser(tokens.subarray(1));
			}
			else { throw std::invalid_argument("Invalid command!"); }
		}
		switch (current->getRole()) {
		case Role::CASHIER:
			CashierCommandHandler::handle(tokens);
			break;
		case Role::MANAGER:
			MangerCommandHandler::handle(tokens);
			break;
		default:
			throw std::runtime_error("Invalid role!");
		}
			/*if (command == "register" ||
				command == "list-user-data" ||
				command == "list-workers" ||
				command == "list-products" ||
				command == "list-feed" ||
				command == "list-transactions" ||
				command == "leave" ||
				command == "logout") {
				CommandHandler::handle(tokens);
			}
			else if (command == "sell") {
				CashierCommandHandler::handle(tokens);
			}
			else if (command == "list-pending" ||
				command == "approve" ||
				command == "decline" ||
				command == "list-warned-cashiers" ||
				command == "warn-cashier" ||
				command == "promote-cashier" ||
				command == "fire-cashier" ||
				command == "add-category" ||
				command == "delete-category" ||
				command == "add-product" ||
				command == "delete-product" ||
				command == "load-products" ||
				command == "load-gift-cards") {
				if (tokens.size() < 2) throw std::invalid_argument("Missing passcode!");
				String passCode = tokens.pop();
				if (Manager::authenticate(passCode)) {
					MangerCommandHandler::handle(tokens);
				}
				else { throw std::invalid_argument("Access denied!"); }
			}
			else { throw std::invalid_argument("Unknown command!"); }
		}*/
	}
	catch (const std::exception& e) {
		throw std::invalid_argument(e.what());
	}
}