#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//models//_Models.h"
#include "CommandHandler.h"

class CashierCommandHandler{
public:
	static void handle(const Vector<String>& tokens);

private:
	static void sell();

    static void promptProductSale();
    static double promptQuantity(Product* product);
    static void sellProduct(Product* product, double quantity);
    static void endTransactionSafely();
};