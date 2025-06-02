#pragma once
#include "..//..//utils//headers//Vector.h"
#include "..//..//utils//headers//String.h"
#include "..//..//core//headers//System.h"
#include "..//..//core//headers//Manager.h"
#include "..//..//CommandHandler.h"

class CommandDispatcher {
public:
	static void dispatch(const String& input, const User* user);
};