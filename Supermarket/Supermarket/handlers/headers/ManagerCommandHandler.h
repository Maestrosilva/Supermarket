#pragma once
#include "..//..//utils//_Utils.h"
#include "CommandHandler.h"

class ManagerCommandHandler{
private:
	static void handle(const Vector<String>& tokens);

	static void sell();

	friend class CommandDispathcer;
};