#include "..//headers//ManagerCommandHandler.h"

void ManagerCommandHandler::handle(const Vector<String>& tokens) {
	try {
		String command = tokens[0];
		if (CommandHandler::handle(tokens));
		else if (command == String("list-pending")) {
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
			addCategory(tokens.subarray(1));
		}
		else if (command == String("delete-category")) {
			deleteCategory(tokens.subarray(1));
		}
		else if (command == String("add-product")) {
			addProduct(tokens.subarray(1));
		}
		else if (command == String("delete-product")) {
			deleteProduct(tokens.subarray(1));
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
	String feed = String("Cashier with id ") + cashierId + String(" has been approved!");
	System::createFeed(feed);
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
	System::removeWorker(cashier);
	String feed = String("Cashier with id ") + cashierId + String(" has been declined!");
	std::cout << feed << std::endl;
	System::createFeed(feed);
}

void ManagerCommandHandler::warn(const Vector<String>& tokens) {
	String cashierId = tokens[0];
	int points = String::toInt(tokens[1]);
	Cashier* cashier = getCashierById(cashierId);
	cashier->addWarning(new Warning(System::current, String("Some description..."), static_cast<DegreeOfCriticality>(points)));
	String feed = String("Cashier with id ") + cashierId + String(" has been warned!");
	std::cout << feed << std::endl;
	System::createFeed(feed);
}

void ManagerCommandHandler::promote(const Vector<String>& tokens) {
	String cashierId = tokens[0];
	String code = tokens[1];
	if (!Manager::authenticate(code)) {
		throw std::runtime_error("Access denied!");
	}
	Cashier* cashier =  getCashierById(cashierId);
	Manager* manager = WorkerFactory::promote(cashier);
	System::removeWorker(cashier);
	System::addWorker(manager);
	String feed = String("Cashier with id ") + manager->getId() + String(" has been promoted!");
	std::cout << feed << std::endl;
	System::createFeed(feed);
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
	System::removeWorker(cashier);
	String feed = String("Cashier with id ") + cashierId + String(" has been fired!");
	std::cout << feed << std::endl;
	System::createFeed(feed);
}

void ManagerCommandHandler::addCategory(const Vector<String>& tokens) {
	String name = tokens[0];
	String description;
	tokens.subarray(1).foreach([&](const String& s) {description.append(s).append(" "); });
	System::addCategory(new Category(name, description));
	String feed = String("Category ") + name + String(" has been added!");
	std::cout << feed << std::endl;
	System::createFeed(feed);
}

void ManagerCommandHandler::deleteCategory(const Vector<String>& tokens) {
	String id = tokens[0];
	System::deleteCategory(System::getCategoryById(id));
	String feed = String("Category with id ") + id + String(" has been removed!");
	std::cout << feed << std::endl;
	System::createFeed(feed);
}

void ManagerCommandHandler::addProduct(const Vector<String>& tokens) {
	ProductType type = ProductType::get(tokens[0]);
	String name = tokens[1];
	String categoryId = tokens[2];
	double price = String::toDouble(tokens[3]);
	System::createProduct(type, name, categoryId, price);
	String feed = String("Product ") + name + String(" has been added!");
	std::cout << feed << std::endl;
	System::createFeed(feed);
}

void ManagerCommandHandler::deleteProduct(const Vector<String>& tokens) {
	String id = tokens[0];
	System::deleteProduct(System::getProductById(id));
	String feed = String("Product with id ") + id + String(" has been removed!");
	std::cout << feed << std::endl;
	System::createFeed(feed);
}

Cashier* ManagerCommandHandler::getCashierById(const String& cashierId) {
	Cashier* cashier = dynamic_cast<Cashier*>(System::getWorkerById(cashierId));
	if (!cashier) {
		throw std::runtime_error("The ID does not belong to a Cashier.");
	}
	return cashier;
}