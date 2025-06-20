#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//models//headers/Transaction.h"
#include "BaseRepository.h"
#include <fstream>

class TransactionRepository : public BaseRepository {
private:
	Vector<Transaction*> transactions;
	static const String TRANSACTIONS_DATA_FILE_NAME;

	TransactionRepository() = default;

	const Vector<Transaction*>& getTransactions();
	Transaction* getById(const String& id);

	void add(Transaction* transaction);
	void remove(Transaction* const transaction);

	void load() override;
	void save() const override;
	void free() override;

	friend class System;
};