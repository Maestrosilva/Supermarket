#include "..//headers//CashierCommandHandler.h"

void CashierCommandHandler::handle(const Vector<String> tokens) {
	try {
		CommandHandler::handle(tokens);
		if (command == "sell") {
			sell();
		}
	}
	catch (std::exception&) {
		throw std::invalid_argument("Something went wrong!");
	}
}

void CashierCommandHandler::sell() {
    System::printProducts();
    System::startTransaction();
    String productInput;
    double quantity;
    while (true) {
        std::cout << "Enter Product Id to sell. Enter 'END' to end the transaction:\n";
        std::cin >> productInput;
        if (productInput == "END") {
            break;
        }
        Product* product = System::getProductById(String::toInt(productInput));
        if (product == nullptr) {
            std::cerr << "Invalid product ID!" << std::endl;
            continue;
        }
        std::cout << "Enter quantity:\n";
        if (!(std::cin >> quantity)) {
            std::cerr << "Invalid quantity input!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        try {
            System::sell(product, quantity);
        }
        catch (const std::runtime_error& e) {
            std::cerr << e.what() << "\n<------------------------>\n";
            continue;
        }
        std::cout << "<------------------------>\n";
    }
    try {
        System::endTransaction();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}