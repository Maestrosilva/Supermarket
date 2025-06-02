#pragma once
#include "..//..//utils//headers//String.h"
#include "..//..//utils//headers//Serializable.h"
#include "Cashier.h"

struct Pair {
	Product* product;
	double quantity;
};

class Transaction : public Serializable {
private:
	const String id;
	const String cashierId;
	const String date;
	Vector<Pair> pairs;

	bool ended = false;
	static constexpr FILE_NAME = "receipt_.txt";
public:
	Transaction(const String cashierId);
	add(const Pair& pair);

	String toString() const;

	void serialize(std::ostream& os) const override;
	void deserialize(std::istream& is) override;

	~Transaction();
};