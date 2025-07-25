#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <numeric>

template<typename T = double>
class Vector {
private:
    std::vector<T> data;
    size_t dimension;

public:
    // Constructors
    Vector() : dimension(0) {}
    Vector(size_t dim) : dimension(dim), data(dim, T(0)) {}
    Vector(size_t dim, const T& value) : dimension(dim), data(dim, value) {}
    Vector(const std::vector<T>& vec) : data(vec), dimension(vec.size()) {}
    Vector(std::initializer_list<T> values) : data(values), dimension(values.size()) {}
    Vector(T x, T y, T z) : data({x, y, z}), dimension(3) {}
    
    // Copy and move constructors
    Vector(const Vector& other) = default;
    Vector(Vector&& other) noexcept = default;
    Vector& operator=(const Vector& other) = default;
    Vector& operator=(Vector&& other) noexcept = default;
    
    // Destructor
    ~Vector() = default;

    // Accessors
    size_t size() const { return dimension; }
    size_t getDimension() const { return dimension; }
    
    // Element access
    T& operator[](size_t index) {
        if (index >= dimension) throw std::out_of_range("Vector index out of range");
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= dimension) throw std::out_of_range("Vector index out of range");
        return data[index];
    }
    
    T& at(size_t index) { return operator[](index); }
    const T& at(size_t index) const { return operator[](index); }

    // Vector operations
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(const T& scalar) const;
    Vector operator/(const T& scalar) const;
    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(const T& scalar);
    Vector& operator/=(const T& scalar);
    
    // Unary operators
    Vector operator-() const;
    
    // Comparison
    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const { return !(*this == other); }

    // Vector products and operations
    T dot(const Vector& other) const;
    Vector cross(const Vector& other) const;  // Only for 3D vectors
    T magnitude() const;
    T magnitudeSquared() const;
    Vector normalize() const;
    Vector& normalizeInPlace();
    
    // Distance functions
    T distance(const Vector& other) const;
    T distanceSquared(const Vector& other) const;
    
    // Angle between vectors
    T angle(const Vector& other) const;
    
    // Projection operations
    Vector project(const Vector& onto) const;
    Vector reject(const Vector& onto) const;
    
    // Component access (for 3D vectors)
    T x() const { return dimension > 0 ? data[0] : T(0); }
    T y() const { return dimension > 1 ? data[1] : T(0); }
    T z() const { return dimension > 2 ? data[2] : T(0); }
    
    void setX(const T& value) { if (dimension > 0) data[0] = value; }
    void setY(const T& value) { if (dimension > 1) data[1] = value; }
    void setZ(const T& value) { if (dimension > 2) data[2] = value; }
    
    // Utility functions
    void fill(const T& value);
    void fillRandom(T min = T(0), T max = T(1));
    void resize(size_t newSize, const T& fillValue = T(0));
    Vector subVector(size_t start, size_t length) const;
    
    // Statistical functions
    T sum() const;
    T mean() const;
    T min() const;
    T max() const;
    
    // Static factory methods
    static Vector zeros(size_t dimension);
    static Vector ones(size_t dimension);
    static Vector random(size_t dimension, T min = T(0), T max = T(1));
    static Vector unitX() { return Vector({T(1), T(0), T(0)}); }
    static Vector unitY() { return Vector({T(0), T(1), T(0)}); }
    static Vector unitZ() { return Vector({T(0), T(0), T(1)}); }
    
    // I/O operations
    void print(std::ostream& os = std::cout, int precision = 6) const;
    void readFromInput(std::istream& is = std::cin);
    
    // Iterator support
    typename std::vector<T>::iterator begin() { return data.begin(); }
    typename std::vector<T>::iterator end() { return data.end(); }
    typename std::vector<T>::const_iterator begin() const { return data.begin(); }
    typename std::vector<T>::const_iterator end() const { return data.end(); }
    
    // Friends
    template<typename U>
    friend Vector<U> operator*(const U& scalar, const Vector<U>& vector);
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vector);
};

// Typedef for common types
using VectorD = Vector<double>;
using VectorF = Vector<float>;
using VectorI = Vector<int>;

#include "Vector.cpp"  // Include implementation for template class
