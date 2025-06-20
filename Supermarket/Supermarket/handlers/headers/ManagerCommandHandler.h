#pragma once
#include "..//..//utils//_Utils.h"
#include "CommandHandler.h"
#include "..//..//core//System.h"

class System;

class ManagerCommandHandler{
public:
	static void handle(const Vector<String>& tokens);

private:
	static void approve(const Vector<String>& tokens);
	static void decline(const Vector<String>& tokens);
	static void warn(const Vector<String>& tokens);
	static void promote(const Vector<String>& tokens);
	static void fire(const Vector<String>& tokens);

	static Cashier* getCashierById(const String& cashierId);
};