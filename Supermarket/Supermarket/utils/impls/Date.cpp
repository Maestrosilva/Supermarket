#include "..//headers//Date.h";

const String& Date::getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    String time("Current time: "
        + String::intToString(localTime->tm_hour) + ":"
        + String::intToString(localTime->tm_min) + ":"
        + String::intToString(localTime->tm_sec));
    return time;
}