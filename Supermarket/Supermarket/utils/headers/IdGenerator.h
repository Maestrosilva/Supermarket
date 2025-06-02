#pragma once
#include "String.h"
#include "..//..//enums//IdType"
#include <fstream>
#include <sstream>



class IdGenerator : Serializable{
    static int getNextId(IdType type) {
        return counters[(int)type]++;
    }

private:
    static int counters[(int)IdType::Count];
};


int IdGenerator::counters[(int)Category::Count] = { 0 };
