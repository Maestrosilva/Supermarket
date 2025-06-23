#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//System.h"

class System;

class CommandHandler {
public:
	static bool handle(const Vector<String>& tokens);
};