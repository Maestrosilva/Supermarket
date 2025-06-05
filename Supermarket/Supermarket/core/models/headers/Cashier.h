#pragma once
#include "Worker.h"
#include "Warning.h"

class Cashier : public Worker {
private:
	size_t transactionsCount = 0;
	Vector<Warning*> warnings;

	bool approved = false;
public:
	Cashier() = default;
	Cashier(const String& firstName, const String& lastName, const String& phoneNumber, unsigned char age, const String& password);

	size_t getTransactionCount() const;
	const Vector<Warning*>& getWarnings() const;
	bool isApproved() const;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is)override;

	const Role& getRole() const override;

	~Cashier();
};