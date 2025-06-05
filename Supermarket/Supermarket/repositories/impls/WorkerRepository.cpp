#include "..//headers//WorkerRepository.h"

const String WorkerRepository::WORKERS_DATA_FILE_NAME = "..//..//data//workers.dat";

const Vector<Worker*>& WorkerRepository::getWorkers() { return workers; }

Worker* WorkerRepository::getById(const String& id) {
    for (size_t i = 0; i < workers.getLength(); i++) {
        if (workers[i]->getId() == id) return workers[i];
    }
    return nullptr;
}

Worker* WorkerRepository::getByIdAndPass(const String& id, const String& pass) {
    for (size_t i = 0; i < workers.getLength(); i++) {
        if (workers[i]->getId() == id && workers[i]->password == Hasher::hash(pass))
            return workers[i];
    }
    return nullptr;
}

void WorkerRepository::add(Worker* worker) { workers.push(worker); }
void WorkerRepository::remove(Worker* const worker) { workers.remove(worker); }

void WorkerRepository::load() {
    free();
    std::ifstream file(WorkerRepository::WORKERS_DATA_FILE_NAME, std::ios::binary);
    if (!file) return;
    size_t length = 0;
    file.read(reinterpret_cast<char*>(&length), sizeof(length));
    for (size_t i = 0; i < length; i++) {
        char roleByte = 0;
        file.read(&roleByte, sizeof(roleByte));
        if (!file) break;
        Role::RoleEnum enumValue = static_cast<Role::RoleEnum>(roleByte);
        Role role(enumValue);
        Worker* worker = WorkerFactory::create(role);
        worker->deserialize(file);
        workers.push(worker);
    }
    file.close();
}

void WorkerRepository::save() const {
    std::ofstream file(WorkerRepository::WORKERS_DATA_FILE_NAME, std::ios::binary | std::ios::trunc);
    if (!file) return;
    size_t length = workers.getLength();
    file.write(reinterpret_cast<const char*>(&length), sizeof(length));
    for (size_t i = 0; i < length; i++) {
        char roleByte = static_cast<char>(static_cast<Role::RoleEnum>(workers[i]->getRole().get()));
        file.write(&roleByte, sizeof(roleByte));
        workers[i]->serialize(file);
    }
    file.close();
}

void WorkerRepository::free() {
    for (size_t i = 0; i < workers.getLength(); i++) {
        delete workers[i];
    }
    workers.clear();
}