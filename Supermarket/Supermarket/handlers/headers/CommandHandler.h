#pragma once
#include "..//..//utils//headers//String.h"
#include "..//..//utils//headers//Vector.h"
#include "..//..//core//headers//System.h"

class CommandHandler {
public:
	static void handle(const Vector<String>& tokens);
};