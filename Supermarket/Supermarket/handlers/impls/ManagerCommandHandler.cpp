#include "..//headers//ManagerCommandHandler.h"

void ManagerCommandHandler::handle(const Vector<String>& tokens) {
	try {
		CommandHandler::handle(tokens);
		String command = tokens[0];
		if (command == String("list-pending")) {
			System::listPending();
		}
		else if (command == String("approve")) {
			approve(tokens.subarray(1));
		}
		else if (command == String("decline")) {
			decline(tokens.subarray(1));
		}
		else if (command == String("list-warn-cashiers")) {
			System::listWarnCashiers(String::toInt(tokens[1]));
		}
		else if (command == String("warn-cashier")) {
			warn(tokens.subarray(1));
		}
		else if (command == String("promote-cashier")) {
			promote(tokens.subarray(1));
		}
		else if (command == String("fire-cashier")) {
			fire(tokens.subarray(1));
		}
		else if (command == String("add-category")) {
			//addCategory(tokens.subarray(1));
		}
		else if (command == String("delete-category")) {
			//deleteCategory(tokens.subarray(1));
		}
		else if (command == String("add-product")) {
			//addProduct(tokens.subarray(1));
		}
		else if (command == String("delete-product")) {
			//deleteProduct(tokens.subarray(1));
		}
		else if (command == String("load-products")) {
			System::refill(tokens[1]);
		}
		else if (command == String("load-gift-cards")) {
			//System::refillGifts(tokens[1]);
		}
		else { throw std::invalid_argument("Invalid command!"); }
	}
	catch (std::out_of_range) {
		throw std::invalid_argument("Invalid format!");
	}
	catch (std::exception& e) {
		throw std::runtime_error(e.what());
	}
}

void ManagerCommandHandler::approve(const Vector<String>& tokens) {
	String cashierId = tokens[0];
	String code = tokens[1];
	if (!Manager::authenticate(code)) {
		throw std::runtime_error("Access denied!");
	}
	Cashier* cashier = getCashierById(cashierId);
	if (cashier->isApproved()) {
		throw std::runtime_error("Cashier already approved!");
	}
	cashier->approve();
	std::cout << "Successful approval of a cashier with id: " << cashier->getId() << std::endl;
}

void ManagerCommandHandler::decline(const Vector<String>& tokens) {
	String cashierId = tokens[0];
	String code = tokens[1];
	if (!Manager::authenticate(code)) {
		throw std::runtime_error("Access denied!");
	}
	Cashier* cashier = getCashierById(cashierId);
	if (cashier->isApproved()) {
		throw std::runtime_error("Cashier already approved!");
	}
	std::cout << "Successful declining of a cashier with id: " << cashier->getId() << std::endl;
	System::removeWorker(cashier);
}

void ManagerCommandHandler::warn(const Vector<String>& tokens) {
	String cashierId = tokens[0];
	int points = String::toInt(tokens[1]);
	Cashier* cashier = getCashierById(cashierId);
	cashier->addWarning(new Warning(System::current, String("Some description..."), static_cast<DegreeOfCriticality>(points)));
	std::cout << "Successful adding of a warning to " << std::endl;
}

void ManagerCommandHandler::promote(const Vector<String>& tokens) {
	String cashierId = tokens[0];
	String code = tokens[1];
	if (!Manager::authenticate(code)) {
		throw std::runtime_error("Access denied!");
	}
	Cashier* cashier =  getCashierById(cashierId);
	Manager* manager = WorkerFactory::promote(cashier);
	System::addWorker(manager);
	System::removeWorker(cashier);
	std::cout << "Successful promotion of cashier with id: " << manager->getId() << std::endl;
}

void ManagerCommandHandler::fire(const Vector<String>& tokens) {
	String cashierId = tokens[0];
	String code = tokens[1];
	if (!Manager::authenticate(code)) {
		throw std::runtime_error("Access denied!");
	}
	Cashier* cashier = getCashierById(cashierId);
	if (!cashier->isApproved()) {
		throw std::runtime_error("No approved cashier with ID: " + cashierId + "!");
	}
	std::cout << "Successful firing of a cashier with id: " << cashier->getId() << std::endl;
	System::removeWorker(cashier);
}

Cashier* ManagerCommandHandler::getCashierById(const String& cashierId) {
	Cashier* cashier = dynamic_cast<Cashier*>(System::getWorkerById(cashierId));
	if (!cashier) {
		throw std::runtime_error("The ID does not belong to a Cashier.");
	}
	return cashier;
}