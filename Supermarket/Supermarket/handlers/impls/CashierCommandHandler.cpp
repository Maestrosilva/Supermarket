#include "..//headers//CashierCommandHandler.h"

void CashierCommandHandler::handle(const Vector<String> tokens) {
	try {
		CommandHandler::handle(tokens);
		if (command == "sell") {
			sell();
		}
	}
	catch (std::exception) {
		throw std::invalid_argument("Something went wrong!");
	}
}

void CashierCommandHandler::sell() {
	std::cout << "Products: " << std::endl;
	size_t counter = 1;
	System::products.foreach([](const Product* p) {
		std::cout << counter++ << ". ";
		std::cout << p->toString() << std::endl;
		});
	String product;
	double quantity;
	Transaction* t(System::current->getId);
	while (true) {
		std::cout << "Enter Product Id to sell. Enter 'END' to end the transaction:" << std::endl;
		std::cin >> product;
		if (product = "END") {
			break;
		}
		Product* p = products[String::toNum(product)];
		std::cout << "Enter quantity:" << std::endl;
		std::cin >> quantity;
		try {
			System::sell(p, quantity);
			t->add(Pair(p, quantity));
		}
		catch (std::runtime_error e) {
			std::cerr << e.what();
			std::cout << "<------------------------>" << std::endl;
			continue;
		}
		std::cout << "<------------------------>" << std::endl;
	}
	System::transactions.push(t);
	System::save();
}