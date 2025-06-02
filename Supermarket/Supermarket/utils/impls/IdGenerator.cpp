#include "IdGenerator.h"

IdGenerator::IdGenerator(const String& fileName) : fileName(fileName) {
    load();
}

void IdGenerator::load() {
    std::ifstream file(fileName.c_str());
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int typeInt;
        size_t value;
        if (iss >> typeInt >> value) {
            if (typeInt >= 0 && typeInt < (int)IdType::COUNT) {
                currentIds[typeInt] = value;
            }
        }
    }

    file.close();
}

void IdGenerator::save() const {
    std::ofstream file(fileName.c_str(), std::ios::trunc);
    if (!file.is_open()) return;

    for (int i = 0; i < (int)IdType::COUNT; ++i) {
        file << i << " " << currentIds[i] << "\n";
    }

    file.close();
}

size_t IdGenerator::next(IdType type) {
    if (type == IdType::ALL) return 0;
    int index = (int)type;
    currentIds[index]++;
    save();
    return currentIds[index];
}

void IdGenerator::reset(IdType type) {
    if (type == IdType::ALL) {
        for (int i = 0; i < (int)IdType::COUNT; ++i) {
            currentIds[i] = 0;
        }
    }
    else {
        currentIds[(int)type] = 0;
    }
    save();
}