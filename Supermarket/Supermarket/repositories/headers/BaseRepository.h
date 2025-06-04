#pragma once
#include "..//..//utils//_Utils.h"
#include "..//..//core//models//headers/Worker.h"
#include "..//..//factories//headers//WorkerFactory.h"
#include <fstream>

class BaseRepository {
public:
    virtual void save() const = 0;
    virtual void load() = 0;
    virtual void free() = 0;
    void reload();

	virtual ~BaseRepository() = default;
};