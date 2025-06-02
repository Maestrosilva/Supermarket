#pragma once
#include "..//..//utils//headers//String.h"
#include "Worker.h"
#include "..//..//enums//Role.h"
#include "..//..//utils//headers//Serializable.h"

class WorkerFactory {

	static Worker* create(const Role role, const String& firstName, const String& lastName,
		const String& phoneNumber, unsigned char age, const String& password) {}
};