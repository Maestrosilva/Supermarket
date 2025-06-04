#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//models//headers/Worker.h"
#include "..//..//factories//headers//WorkerFactory.h"
#include "BaseRepository.h"
#include <fstream>

class WorkerRepository : public BaseRepository {
private:
	Vector<Worker*> workers;
	static constexpr String WORKERS_DATA_FILE_NAME = "..//..//data//workers.dat";

	WorkerRepository() = default;

	const Vector<Worker*>& getWorkers();
	Worker* getById(const String& id);
	Worker* getByIdAndPass(const String& id, const String& pass);

	void add(Worker* worker);
	void remove(const Worker* worker);

	void load() override;
	void save() const override;
	void free() override;

	friend class System;
};