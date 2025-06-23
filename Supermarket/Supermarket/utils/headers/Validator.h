#pragma once
#include "String.h"

class Validator {
public:
	static void validateName(const String& name);
	static void validatePhoneNumber(const String& name);
	static void validateAge(unsigned char age);
	static void validatePassword(const String& name);
	//static void validateAuthenticationCode(const String& name);
};