#pragma once
#include "..//..//utils//headers//String.h"
#include "..//..//utils//headers//Vector.h"
#include "Worker.h"

class Manager : public Worker{
private:
	static constexpr String specialCode = "SPEZIALEN_E";

public:
	Manager() = default;
	Manager(const String& firstName, const String& lastName, const String& phoneNumber, unsigned char age, const String& password);

	static bool authenticate(const String& specialCode);
};