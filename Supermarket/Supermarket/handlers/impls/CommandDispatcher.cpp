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
			else if (command == "register") {
				System::registerUser(tokens.subarray(1));
			}
			else { throw std::invalid_argument("Invalid command!"); }
		}
		switch (current->getRole()) {
		case Role::CASHIER:
			CashierCommandHandler::handle(tokens);
			break;
		case Role::MANAGER:
			ManagerCommandHandler::handle(tokens);
			break;
		default:
			throw std::runtime_error("Invalid role!");
		}
	}
	catch (const std::exception& e) {
		throw std::invalid_argument(e.what());
	}
}