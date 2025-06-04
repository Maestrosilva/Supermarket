#include "..//..//utils//headers//IdGenerator.h"

int IdGenerator::next(IdType type) {
    return ++counters[(int)type];
}

void IdGenerator::serialize(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) return;

    for (int i = 0; i < (int)IdType::Count; i++) {
        ofs.write(reinterpret_cast<const char*>(&counters[i]), sizeof(int));
    }
}

void IdGenerator::deserialize(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) return;

    for (int i = 0; i < (int)IdType::Count; i++) {
        ifs.read(reinterpret_cast<char*>(&counters[i]), sizeof(int));
    }
}