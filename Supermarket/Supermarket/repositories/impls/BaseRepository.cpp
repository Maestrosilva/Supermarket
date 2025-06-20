#include "..//headers//BaseRepository.h"

void BaseRepository::reload() {
    save();
    //free();
    load();
}