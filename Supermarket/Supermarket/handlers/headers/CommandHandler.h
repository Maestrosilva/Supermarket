#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//System.h"

class CommandHandler {
private:
	static void handle(const Vector<String>& tokens);

	friend class CommandDispatcher;
};