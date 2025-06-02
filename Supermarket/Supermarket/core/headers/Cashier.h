#pragma once
#include "..//..//utils//headers//String.h"
#include "..//..//utils//headers//Vector.h"
#include "Worker.h"
#include "Warning.h"

class Cashier : public Worker{
private:
	size_t transactionsCount = 0;
	Vector<Warning> warnings;

	bool approved = false;
public:
	Cashier();
	Cashier(const String& firstName, const String& lastName, const String& phoneNumber, unsigned char age, const String& password);

	size_t getTransactionCount() const;
	const Vector<Warning>& getWarnings() const;

	Role getRole() const;
};