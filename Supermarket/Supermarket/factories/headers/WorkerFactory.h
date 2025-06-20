#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//enums//Role.h"
#include "..//..//core//models//headers//Worker.h"
#include "..//..//core//models//headers//Cashier.h"
#include "..//..//core//models//headers//Manager.h"

class WorkerFactory {
public:
	static Worker* create(bool creational, const Role& role, const String& firstName = "", const String& lastName = "", const String& phoneNumber = "", unsigned char age = 0, const String& password = "");
	static Manager* promote(const Cashier* cashier);
};