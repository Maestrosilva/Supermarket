#include "..//headers//Date.h";

const String Date::getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    String dateStr(
        String::intToString(localTime->tm_year + 1900) + "-" +
        (localTime->tm_mon + 1 < 10 ? "0" : "") + String::intToString(localTime->tm_mon + 1) + "-" +
        (localTime->tm_mday < 10 ? "0" : "") + String::intToString(localTime->tm_mday) + " " +
        (localTime->tm_hour < 10 ? "0" : "") + String::intToString(localTime->tm_hour) + ":" +
        (localTime->tm_min < 10 ? "0" : "") + String::intToString(localTime->tm_min) + ":" +
        (localTime->tm_sec < 10 ? "0" : "") + String::intToString(localTime->tm_sec)
    );
    return dateStr;
}