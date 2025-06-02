#include "..//headers//Date.h";

const String& Date::getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    String time("Current time: "
        + localTime->hour << ":"
        + localTime->min << ":"
        + localTime->sec << std::endl);

    return time;
}