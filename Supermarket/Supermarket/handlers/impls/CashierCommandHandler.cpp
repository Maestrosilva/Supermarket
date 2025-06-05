#include "..//headers//CashierCommandHandler.h"

void CashierCommandHandler::handle(const Vector<String>& tokens) {
	try {
		CommandHandler::handle(tokens);
        String command = tokens[0];
		if (command == String("sell")) {
			sell();
		}
	}
	catch (std::exception&) {
		throw std::invalid_argument("Something went wrong!");
	}
}

void CashierCommandHandler::sell() {
    System::displayAllProducts();
    promptProductSale();
    endTransactionSafely();
}

void CashierCommandHandler::promptProductSale() {
    String productInput;
    double quantity;
    while (true) {
        std::cout << "Enter Product Id to sell. Enter 'END' to end the transaction:\n";
        std::cout << ">";
        std::cin >> productInput;
        if (productInput == String("END")) break;
        Product* product = System::getProductById(String::toInt(productInput));
        if (!product) {
            std::cerr << "Invalid product ID!" << std::endl;
            continue;
        }
        quantity = promptQuantity(product);
        if (quantity < 0) continue;
        sellProduct(product, quantity);
        std::cout << "<------------------------>\n";
    }
}

double CashierCommandHandler::promptQuantity(Product* product) {
    double quantity;
    std::cout << "Enter quantity:";
    if (product->getType() == ProductType::BY_UNIT)
        std::cout << " (units)";
    std::cout << "\n";
    if (!(std::cin >> quantity)) {
        std::cerr << "Invalid quantity input!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    return quantity;
}

void CashierCommandHandler::sellProduct(Product* product, double quantity) {
    try {
        System::sell(product, quantity);
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n<------------------------>\n";
    }
}

void CashierCommandHandler::endTransactionSafely() {
    try {
        System::endTransaction();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}