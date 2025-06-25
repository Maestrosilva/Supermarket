#include "..//..//utils//headers//IdGenerator.h"

int IdGenerator::counters[(int)IdType::COUNT] = { 0 };

int IdGenerator::next(IdType type) {
    return ++counters[(int)type];
}

void IdGenerator::rollback(IdType type) {
    --counters[(int)type];
}

void IdGenerator::serialize(std::ostream& os) {
    for (int i = 0; i < (int)IdType::COUNT; i++) {
        os.write(reinterpret_cast<const char*>(&counters[i]), sizeof(int));
    }
}

void IdGenerator::deserialize(std::istream& is) {
    for (int i = 0; i < (int)IdType::COUNT; i++) {
        is.read(reinterpret_cast<char*>(&counters[i]), sizeof(int));
    }
}

void IdGenerator::reload() {
    std::ofstream os("data//ids.dat", std::ios::binary, std::ios::trunc);
    IdGenerator::serialize(os);
    os.close();
    std::ifstream is("data//ids.dat", std::ios::binary);
    IdGenerator::deserialize(is);
    is.close();
}