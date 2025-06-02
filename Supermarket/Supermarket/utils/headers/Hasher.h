#pragma once
#include "String.h"

class Hasher {
private:
	static const char key = 'K';

public:
	static String hash(const String& str);
	static String encrypt(const String& str);
	static String decrypt(const String& str);
};