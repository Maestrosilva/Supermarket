#pragma once
#include <iostream>
#include <stdexcept>
#include <cstdlib> 
#include <ctime> 
#include "String.h"

template <typename T>
class Vector : public Serializable {
private:
    T* data = nullptr;
    size_t length = 0;
    size_t capacity = 0;

    static const size_t DEFAULT_CAPACITY = 10;
    static const size_t RESIZE_FACTOR = 2;
    static const size_t SHRINK_THRESHOLD = 3;

    void free();
    void copyFrom(const Vector& other);
    void resize(char ch = '+');
    static void populate(T*& destination, const T* source, size_t length);

public:
    Vector(size_t capacity = DEFAULT_CAPACITY);
    Vector(const T* data, size_t length);
    Vector(const Vector& other);

    Vector& operator=(const Vector& other);

    size_t getLength() const;
    size_t getCapacity() const;
    T* getData() const;
    T& get(size_t index) const;

    void out(std::ostream& direction = std::cout, const String& delimiter = ", ") const;

    Vector& push(const T& element);
    T& pop();
    T& peek() const;

    void add(const T& element, size_t index);
    void add(const Vector& vect, size_t index);

    Vector& remove(const T& element);
    void removeAt(size_t index);

    void setAt(size_t index, const T& toSet);
    short indexOf(const T& element) const;

    bool contains(const T& element) const;

    void reverse();
    Vector reversed() const;

    void sort();
    Vector sorted() const;

    template <typename Func>
    void map(Func func);

    template <typename Func>
    Vector mapped(Func func) const;

    template <typename Func>
    void foreach(Func func) const;

    template <typename Predicate>
    void filter(Predicate predicate);

    template <typename Predicate>
    Vector filtered(Predicate predicate) const;

    template <typename Predicate>
    T* find(Predicate predicate) const;

    void shuffle();
    Vector shuffled() const;

    Vector subarray(size_t start, short len = -1) const;

    bool isSubArrOf(const Vector& vect) const;
    bool isSubSetOf(Vector<T> vect) const;

    Vector distinct() const;

    bool isEmpty() const;
    void clear();

    T& min() const;
    T& max() const;

    bool operator==(const Vector& vect) const;
    bool operator!=(const Vector& vect) const;
    T& operator[](size_t index) const;
};

#include "..//impls//Vector.cpp"