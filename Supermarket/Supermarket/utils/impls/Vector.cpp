#pragma once
#include "..//headers//Vector.h"
#include "..//headers//String.h"

template <typename T>
void Vector<T>::free() {
    delete[] this->data;
    this->data = nullptr;
    this->length = 0;
    this->capacity = 0;
}

template <typename T>
void Vector<T>::copyFrom(const Vector& other) {
    this->data = new T[other.getLength()];
    populate(this->data, other.getData(), other.getLength());
    this->length = other.getLength();
    this->capacity = other.getCapacity();
}

template <typename T>
void Vector<T>::resize(char ch) {
    switch (ch) {
    case '+':
        this->capacity *= RESIZE_FACTOR;
        break;
    case '-':
        if (this->capacity > this->length) {
            this->capacity /= RESIZE_FACTOR;
        }
        break;
    default:
        throw std::invalid_argument("Invalid resize argument!");
    }
    T* newData = new T[this->capacity];
    populate(newData, this->data, this->length);
    delete[] this->data;
    this->data = newData;
}

template <typename T>
void Vector<T>::populate(T*& destination, const T* source, size_t length) {
    if (destination == nullptr || source == nullptr) {
        throw std::runtime_error("Null pointer dereferenced!");
    }
    for (size_t i = 0; i < length; i++) {
        destination[i] = T(source[i]);
    }
}


template <typename T>
Vector<T>::Vector(size_t capacity) {
    if (capacity == 0) {
        throw std::invalid_argument("Capacity cannot be 0!");
    }
    this->data = new T[capacity];
    this->capacity = capacity;
    this->length = 0;
    srand(time(0));
}

template <typename T>
Vector<T>::Vector(const T* data, size_t length) {
    this->capacity = length * RESIZE_FACTOR;
    this->length = length;
    this->data = new T[capacity];
    populate(this->data, data, length);
    srand(time(0));
}

template <typename T>
Vector<T>::Vector(const Vector& other) {
    copyFrom(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
size_t Vector<T>::getLength() const {
    return this->length;
}

template <typename T>
size_t Vector<T>::getCapacity() const {
    return this->capacity;
}

template <typename T>
T* Vector<T>::getData() const {
    return this->data;
}

template <typename T>
T& Vector<T>::get(size_t index) const {
    if (index >= this->length) {
        throw std::out_of_range("Index out of bounds!");
    }
    return this->data[index];
}

template <typename T>
void Vector<T>::out(std::ostream& direction, const String& delimiter) const {
    direction << "[";
    for (size_t i = 0; i < this->length - 1; i++) {
        direction << (this->data[i]) << delimiter;
    }
    direction << this->data[length - 1];
    direction << "]" << std::endl;
}

template <typename T>
Vector<T>& Vector<T>::push(const T& element) {
    add(element, this->length);
    return *this;
}

template <typename T>
T& Vector<T>::pop() {
    T& toReturn = this->data[length - 1];
    removeAt(this->length - 1);
    return toReturn;
}

template <typename T>
T& Vector<T>::peek() const {
    return this->data[length - 1];
}

template <typename T>
void Vector<T>::add(const T& element, size_t index) {
    if (index > this->length) {
        throw std::out_of_range("Index out of bounds!");
    }
    if (length == capacity) {
        resize('+');
    }
    for (size_t i = this->length; i > index; --i) {
        this->data[i] = this->data[i - 1];
    }
    this->data[index] = element;
    this->length++;
}

template <typename T>
void Vector<T>::add(const Vector<T>& vect, size_t index) {
    for (size_t i = 0; i < vect.getLength(); ++i) {
        this->add(vect[i], index + i);
    }
}

template <typename T>
bool Vector<T>::remove(const T& element) {
    short from = indexOf(element);
    if (from == -1) return false;
    removeAt(from);
    return true;
}

template <typename T>
void Vector<T>::removeAt(size_t index) {
    if (index >= this->length) {
        throw std::out_of_range("Index out of bounds!");
    }
    for (size_t i = index; i < this->length - 1; ++i) {
        this->data[i] = this->data[i + 1];
    }
    this->length--;
    if (this->length * SHRINK_THRESHOLD < this->capacity) {
        resize('-');
    }
}

template <typename T>
void Vector<T>::setAt(size_t index, const T& toSet) {
    this->data[index] = toSet;
}

template <typename T>
short Vector<T>::indexOf(const T& element) const {
    for (size_t i = 0; i < this->length; i++) {
        if (this->data[i] == element) {
            return i;
        }
    }
    return -1;
}

template <typename T>
bool Vector<T>::contains(const T& element) const {
    return indexOf(element) != -1;
}

template <typename T>
void Vector<T>::reverse() {
    for (size_t i = 0; i < this->length / 2; i++) {
        std::swap(this->data[i], this->data[this->length - i - 1]);
    }
}

template <typename T>
Vector<T> Vector<T>::reversed() const {
    Vector vect(*this);
    vect.reverse();
    return vect;
}

template <typename T>
void Vector<T>::sort() {
    for (size_t i = 0; i < this->length; i++) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < this->length; j++) {
            if (this->data[minIndex] > this->data[j]) {
                minIndex = j;
            }
        }
        std::swap(this->data[i], this->data[minIndex]);
    }
}

template <typename T>
Vector<T> Vector<T>::sorted() const {
    Vector vect(*this);
    vect.sort();
    return vect;
}

template <typename T>
template <typename Func>
void Vector<T>::map(Func func) {
    for (size_t i = 0; i < this->length; i++) {
        this->data[i] = func(this->data[i]);
    }
}

template <typename T>
template <typename Func>
Vector<T> Vector<T>::mapped(Func func) const {
    Vector<T> vect;
    vect.reserve(this->length);
    this->foreach([&vect, &func](const T& e) {
        vect.push(func(e));
        });
    return vect;
}

template <typename T>
template <typename Func>
void Vector<T>::foreach(Func func) const {
    for (size_t i = 0; i < this->length; i++) {
        func(this->data[i]);
    }
}

template <typename T>
template <typename Predicate>
void Vector<T>::filter(Predicate predicate) {
    Vector<T> filteredVec;
    for (size_t i = 0; i < this->length; i++) {
        if (predicate(this->data[i])) {
            filteredVec.push(this->data[i]);
        }
    }
    *this = filteredVec;
}

template <typename T>
template <typename Predicate>
Vector<T> Vector<T>::filtered(Predicate predicate) const {
    Vector<T> result;
    result.reserve(this->length);
    for (size_t i = 0; i < this->length; i++) {
        if (predicate(this->data[i])) {
            result.push(this->data[i]);
        }
    }
    return result;
}

template <typename T>
template <typename Predicate>
T* Vector<T>::find(Predicate predicate) const {
    for (size_t i = 0; i < this->length; i++) {
        if (predicate(this->data[i])) {
            return &data[i];
        }
    }
    return nullptr;
}

template <typename T>
void Vector<T>::shuffle() {
    for (size_t i = 0; i < this->length; i++) {
        std::swap(this->data[i], this->data[rand() % this->length]);
    }
}

template <typename T>
Vector<T> Vector<T>::shuffled() const {
    Vector vect(*this);
    vect.shuffle();
    return vect;
}

template <typename T>
Vector<T> Vector<T>::subarray(size_t start, short len) const {
    if (len == -1) {
        len = this->length - start;
    }
    if (start + len > this->length) {
        throw std::out_of_range("Subarray range out of bounds!");
    }
    Vector<T> toReturn;
    for (size_t i = start; i < start + len; i++) {
        toReturn.push(this->data[i]);
    }
    return toReturn;
}

template <typename T>
bool Vector<T>::isSubArrOf(const Vector<T>& vect) const {
    size_t i = 0;
    size_t j = 0;
    while (i < this->length && j < vect.getLength()) {
        if (this->data[i] == vect.get(j)) {
            ++i;
        }
        ++j;
    }
    return i == this->length;
}

template <typename T>
bool Vector<T>::isSubSetOf(Vector<T> vect) const {
    for (size_t i = 0; i < this->length; i++) {
        if (!vect.contains(this[i])) {
            return false;
        }
    }
    return true;
}

template <typename T>
Vector<T> Vector<T>::distinct() const {
    Vector<T> toReturn;
    for (size_t i = 0; i < this->length; i++) {
        if (!toReturn.contains(this->data[i])) {
            toReturn.push(this->data[i]);
        }
    }
    return toReturn;
}

template <typename T>
bool Vector<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
void Vector<T>::clear() {
    free();
    this->capacity = DEFAULT_CAPACITY;
    this->data = new T[this->capacity];
    this->length = 0;
}

template <typename T>
T& Vector<T>::min() const {
    T& min = this->data[0];
    for (size_t i = 1; i < this->length; i++) {
        if (min > this->data[i]) {
            min = this->data[i];
        }
    }
    return min;
}

template <typename T>
T& Vector<T>::max() const {
    T& max = this->data[0];
    for (size_t i = 1; i < this->length; i++) {
        if (max < this->data[i]) {
            max = this->data[i];
        }
    }
    return max;
}

template <typename T>
bool Vector<T>::operator==(const Vector& vect) const {
    if (this->length != vect.getLength()) {
        return false;
    }
    for (size_t i = 0; i < this->length; i++) {
        if (this->data[i] != vect[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector& vect) const {
    return !(*this == vect);
}

template <typename T>
T& Vector<T>::operator[](size_t index) const {
    if (index >= this->length) {
        throw std::out_of_range("Index out of bounds!");
    }
    return this->data[index];
}