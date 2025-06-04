#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//System.h"
#include "..//..//core//models//headers//Worker.h"
#include "..//..//core//models//headers//Cashier.h"
#include "..//..//core//models//headers//Manager.h"
#include "CommandHandler.h"
#include "CashierCommandHandler.h"
#include "ManagerCommandHandler.h"

class CommandDispatcher {
private:
	static void dispatch(const String& input, const Worker* user);

	friend class System;
};