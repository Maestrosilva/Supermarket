#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//models//headers/Transaction.h"
#include "BaseRepository.h"
#include <fstream>

class TransactionRepository : public BaseRepository {
private:
	Vector<Transaction*> transactions;
	static constexpr String TRANSACTIONS_DATA_FILE_NAME = "..//..//data//transactions.dat";

	TransactionRepository() = default;

	const Vector<Transaction*>& getTransaction();
	const Transaction* getById(const String& id);

	void add(Transaction* transaction);
	void remove(const Transaction* transaction);

	void load() override;
	void save() const override;
	void free() override;

	friend class System;
};