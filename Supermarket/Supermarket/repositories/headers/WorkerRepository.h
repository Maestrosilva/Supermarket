#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//models//headers/Worker.h"
#include "..//..//factories//headers//WorkerFactory.h"
#include "BaseRepository.h"
#include <fstream>

class WorkerRepository : public BaseRepository {
private:
	Vector<Worker*> workers;
	static const String WORKERS_DATA_FILE_NAME;

	WorkerRepository() = default;

	const Vector<Worker*>& getWorkers();
	Worker* getById(const String& id);
	Worker* getByIdAndPass(const String& id, const String& pass);
	Worker* getByName(const String& firstName, const String& lastName);

	void add(Worker* worker);
	void remove(Worker* const worker);

	void load() override;
	void save() const override;
	void free() override;

	friend class System;
};