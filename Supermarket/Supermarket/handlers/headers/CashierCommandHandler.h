#pragma once
#include "..//..//utils//headers//String.h"
#include "..//..//utils//headers//Vector.h"
#include "..//..//core//headers//System.h"
#include "CommandHandler.h"

class CashierCommandHandler{
private:
	static void sell();
public:
	static void handle(const Vector<String>& tokens);
};