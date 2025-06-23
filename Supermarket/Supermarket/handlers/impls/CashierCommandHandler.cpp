#include "..//headers//CashierCommandHandler.h"

void CashierCommandHandler::handle(const Vector<String>& tokens) {
	try {
        String command = tokens[0];
        if (CommandHandler::handle(tokens));
		else if (command == String("sell")) {
			sell();
		}
        else { 
            throw std::invalid_argument("Invalid command!");
        }
	}
    catch (std::out_of_range) {
        throw std::invalid_argument("Invalid format!");
    }
    catch (std::exception& e) {
        throw std::runtime_error(e.what());
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
        std::cout << "> ";
        readLine(std::cin, productInput);
        if (productInput.trimmed() == String("END")) break;
        Product* product = System::getProductById(productInput);
        if (!product) {
            std::cerr << "Invalid product ID!" << std::endl;
            continue;
        }
        quantity = promptQuantity(product);
        if (quantity < 0) continue;
        sellProduct(product, quantity);
        std::cout << "\n\n<------------------------>\n\n";
    }
}

double CashierCommandHandler::promptQuantity(Product* product) {
    String q;
    double quantity;
    std::cout << "Enter quantity:";
    if (product->getType() == ProductType::BY_UNIT) {
        std::cout << " (units)";
    }
    std::cout << "\n";
    std::cout << "> ";
    readLine(std::cin, q);
    quantity = String::toDouble(q);
    if (quantity < 0) {
        throw std::invalid_argument("Quantity must be positive number!");
    }
    return quantity;
}

void CashierCommandHandler::sellProduct(Product* product, double quantity) {
    try {
        System::sell(product, quantity);
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
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