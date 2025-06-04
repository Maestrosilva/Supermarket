#include "..//headers//String.h"

void String::free() {
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

void String::copyFrom(const String& other) {
    size = other.size;
    capacity = other.capacity;
    data = new char[capacity];
    strcpy(data, other.data);
}

void String::resize(char ch) {
    switch (ch) {
    case '+':
        capacity *= RESIZE_FACTOR;
        break;
    case '-':
        if (capacity > size) {
            capacity /= RESIZE_FACTOR;
        }
        break;
    default:
        throw std::invalid_argument("Invalid resize argument!");
    }

    char* newData = new char[capacity];
    strcpy(newData, data);
    delete[] data;
    data = newData;
}

String::String(const char* data) {
    size = strlen(data);
    capacity = (size + 1) * RESIZE_FACTOR;
    this->data = new char[capacity];
    strcpy(this->data, data);
}

String::String(size_t capacity) : capacity(capacity) {
    if (capacity == 0) {
        throw std::invalid_argument("Capacity cannot be 0!");
    }
    size = 0;
    data = new char[capacity];
    data[0] = '\0';
}

String::String(const String& other) {
    copyFrom(other);
}

String& String::operator=(const String& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

size_t String::getSize() const { return size; }

size_t String::getCapacity() const { return capacity; }

char String::getChar(size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of bounds!");
    return data[index];
}

void String::out(std::ostream& direction) const {
    direction << (data ? data : "");
}

void String::insert(char ch, size_t index) {
    if (index > size) throw std::out_of_range("Index out of bounds!");
    if (size + 1 >= capacity) resize('+');

    for (size_t i = size; i > index; --i) {
        data[i] = data[i - 1];
    }

    data[index] = ch;
    ++size;
    data[size] = '\0';
}

void String::insert(const String& str, size_t index) {
    for (size_t i = 0; i < str.size; ++i) {
        insert(str.getChar(i), index + i);
    }
}

String& String::append(const String& str) {
    insert(str, size);
    return *this;
}

String& String::append(char ch) {
    insert(ch, size);
    return *this;
}

void String::removeAt(size_t index) {
    if (index >= size) throw std::out_of_range("Index out of bounds!");
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
    data[size] = '\0';

    if (size * SHRINK_THRESHOLD < capacity) {
        resize('-');
    }
}

String& String::remove(const String& substr) {
    short from = indexOf(substr);
    if (from == -1) return *this;
    for (size_t i = 0; i < substr.getSize(); ++i) {
        removeAt(from);
    }
    return *this;
}

short String::indexOf(const String& str) const {
    if (str.size > size) return -1;
    if (str.size == 0) return 0;
    for (size_t i = 0; i <= size - str.size; ++i) {
        bool isSubstr = true;
        for (size_t j = 0; j < str.size; ++j) {
            if (data[i + j] != str.data[j]) {
                isSubstr = false;
                break;
            }
        }
        if (isSubstr) return i;
    }
    return -1;
}

bool String::contains(const String& str) const {
    return indexOf(str) >= 0;
}

void String::setCharAt(char ch, size_t index) {
    if (index >= size) throw std::out_of_range("Index out of bounds!");
    data[index] = ch;
}

void String::replaceAll(const String& oldStr, const String& newStr) {
    short index = indexOf(oldStr);
    while (index != -1) {
        remove(oldStr);
        insert(newStr, index);
        index = indexOf(oldStr);
    }
}

void String::reverse() {
    for (size_t i = 0; i < size / 2; ++i) {
        std::swap(data[i], data[size - i - 1]);
    }
    data[size] = '\0';
}

String String::reversed() const {
    String toReturn = *this;
    toReturn.reverse();
    return toReturn;
}

void String::trim() {
    while (size > 0 && data[0] == ' ') {
        removeAt(0);
    }
    while (size > 0 && data[size - 1] == ' ') {
        removeAt(size - 1);
    }
}

String String::trimmed() const {
    String toReturn = *this;
    toReturn.trim();
    return toReturn;
}

bool String::startsWith(const String& prefix) const {
    return indexOf(prefix) == 0;
}

bool String::endsWith(const String& suffix) const {
    return reversed().startsWith(suffix.reversed());
}

void String::toUpper() {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] >= 'a' && data[i] <= 'z') {
            data[i] -= ('a' - 'A');
        }
    }
}

String String::uppered() const {
    String toReturn = *this;
    toReturn.toUpper();
    return toReturn;
}

void String::toLower() {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            data[i] += ('a' - 'A');
        }
    }
}

String String::lowered() const {
    String toReturn = *this;
    toReturn.toLower();
    return toReturn;
}

Vector<String> String::split(char delimiter) const {
    Vector<String> result;
    size_t start = 0;
    for (size_t i = 0; i <= size; ++i) {
        if (data[i] == delimiter || data[i] == '\0') {
            if (i > start) {
                String token(substr(start, i - start));
                result.push(token);
            }
            start = i + 1;
        }
    }
    return result;
}

String String::substr(size_t start, short len) const {
    if (len == -1) {
        len = size - start;
    }
    if (start + len > size) {
        throw std::out_of_range("Substring range out of bounds");
    }

    String result;
    for (size_t i = start; i < start + len; ++i) {
        result.append(data[i]);
    }
    return result;
}

bool String::isEmpty() const {
    return size == 0;
}

bool String::isBlank() const {
    return trimmed().isEmpty();
}

void String::clear() {
    free();
    capacity = DEFAULT_CAPACITY;
    data = new char[capacity];
    data[0] = '\0';
    size = 0;
}

String String::operator+=(const String& other) {
    return append(other);
}

bool String::operator<(const String& other) { return strcmp(data, other.data) < 0; }
bool String::operator<=(const String& other) { return strcmp(data, other.data) <= 0; }
bool String::operator>(const String& other) { return strcmp(data, other.data) > 0; }
bool String::operator>=(const String& other) { return strcmp(data, other.data) >= 0; }
bool String::operator==(const String& other) { return strcmp(data, other.data) == 0; }
bool String::operator!=(const String& other) { return strcmp(data, other.data) != 0; }

char& String::operator[](size_t index) const {
    if (index >= size) throw std::out_of_range("Index out of bounds!");
    return data[index];
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    str.out(os);
    return os;
}

std::istream& operator>>(std::istream& in, String& str) {
    const size_t BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];
    in >> buffer;
    str = String(buffer);
    return in;
}

String operator+(const String& lhs, const String& rhs) {
    String result(lhs);
    result.append(rhs);
    return result;
}

String String::integerToString(long long num) {
    if (num == 0) return String("0");

    String result;
    bool isNegative = false;
    if (num < 0) {
        isNegative = true;
        num = -num;
    }

    while (num) {
        result.append('0' + (num % 10));
        num /= 10;
    }
    if (isNegative) {
        result.append('-');
    }

    return result.reversed();
}

long long String::toInt(const String& str) {
    if (str.isEmpty()) return 0;
    long long result = 0;
    bool isNegative = false;
    size_t start = 0;
    if (str[0] == '-') {
        isNegative = true;
        start = 1;
    }
    for (size_t i = start; i < str.getSize(); ++i) {
        if (str[i] < '0' || str[i] > '9') {
            throw std::invalid_argument("Invalid number format!");
        }
        result = result * 10 + (str[i] - '0');
    }
    return isNegative ? -result : result;
}

String String::doubleToString(double value, unsigned char precision) {
    char buffer[64];
    char format[10];
    std::snprintf(format, sizeof(format), "%%.%df", precision);
    std::snprintf(buffer, sizeof(buffer), format, value);
    return String(buffer);
}

double String::toDouble(const String& str) {
    double result = 0.0;
    double fraction = 0.0;
    double divisor = 10.0;
    bool negative = false;
    bool pastDecimal = false;
    size_t i = 0;
    if (str[i] == '-') {
        negative = true;
        i++;
    }
    else if (str[i] == '+') {
        i++;
    }
    for (; str[i] != '\0'; ++i) {
        if (str[i] == '.') {
            if (pastDecimal) break;
            pastDecimal = true;
        }
        else if (str[i] >= '0' && str[i] <= '9') {
            int digit = str[i] - '0';
            if (!pastDecimal) {
                result = result * 10.0 + digit;
            }
            else {
                fraction += digit / divisor;
                divisor *= 10.0;
            }
        }
        else {
            std::invalid_argument("Invalid double format!");
        }
    }
    result += fraction;
    if (negative) result = -result;
    return result;
}

const char* String::operator const char* () const {
    return data;
}

void String::serialize(std::ostream& os) const {
    os.write((const char*)&size, sizeof(size));
    os.write(data, size);
}

void String::deserialize(std::istream& is) {
    size_t newSize;
    is.read((char*)&newSize, sizeof(newSize));

    free();

    capacity = newSize > DEFAULT_CAPACITY ? newSize : DEFAULT_CAPACITY;
    data = new char[capacity];
    size = newSize;

    is.read(data, size);
    data[size] = '\0';
}

String::~String() {
    free();
}