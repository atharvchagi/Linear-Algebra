#include "Vector.h"
#include <random>
#include <iomanip>

// Addition operator
template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
    if (dimension != other.dimension) {
        throw std::invalid_argument("Vector dimensions must match for addition");
    }
    
    Vector<T> result(dimension);
    for (size_t i = 0; i < dimension; ++i) {
        result.data[i] = data[i] + other.data[i];
    }
    return result;
}

// Subtraction operator
template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) const {
    if (dimension != other.dimension) {
        throw std::invalid_argument("Vector dimensions must match for subtraction");
    }
    
    Vector<T> result(dimension);
    for (size_t i = 0; i < dimension; ++i) {
        result.data[i] = data[i] - other.data[i];
    }
    return result;
}

// Scalar multiplication
template<typename T>
Vector<T> Vector<T>::operator*(const T& scalar) const {
    Vector<T> result(dimension);
    for (size_t i = 0; i < dimension; ++i) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

// Scalar division
template<typename T>
Vector<T> Vector<T>::operator/(const T& scalar) const {
    if (std::abs(scalar) < std::numeric_limits<T>::epsilon()) {
        throw std::invalid_argument("Division by zero");
    }
    
    Vector<T> result(dimension);
    T inv_scalar = T(1) / scalar;
    for (size_t i = 0; i < dimension; ++i) {
        result.data[i] = data[i] * inv_scalar;
    }
    return result;
}

// Addition assignment
template<typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    if (dimension != other.dimension) {
        throw std::invalid_argument("Vector dimensions must match for addition");
    }
    
    for (size_t i = 0; i < dimension; ++i) {
        data[i] += other.data[i];
    }
    return *this;
}

// Subtraction assignment
template<typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other) {
    if (dimension != other.dimension) {
        throw std::invalid_argument("Vector dimensions must match for subtraction");
    }
    
    for (size_t i = 0; i < dimension; ++i) {
        data[i] -= other.data[i];
    }
    return *this;
}

// Scalar multiplication assignment
template<typename T>
Vector<T>& Vector<T>::operator*=(const T& scalar) {
    for (size_t i = 0; i < dimension; ++i) {
        data[i] *= scalar;
    }
    return *this;
}

// Scalar division assignment
template<typename T>
Vector<T>& Vector<T>::operator/=(const T& scalar) {
    if (std::abs(scalar) < std::numeric_limits<T>::epsilon()) {
        throw std::invalid_argument("Division by zero");
    }
    
    T inv_scalar = T(1) / scalar;
    for (size_t i = 0; i < dimension; ++i) {
        data[i] *= inv_scalar;
    }
    return *this;
}

// Unary minus
template<typename T>
Vector<T> Vector<T>::operator-() const {
    Vector<T> result(dimension);
    for (size_t i = 0; i < dimension; ++i) {
        result.data[i] = -data[i];
    }
    return result;
}

// Equality comparison
template<typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
    if (dimension != other.dimension) return false;
    
    const T EPSILON = std::numeric_limits<T>::epsilon() * 10;
    for (size_t i = 0; i < dimension; ++i) {
        if (std::abs(data[i] - other.data[i]) > EPSILON) return false;
    }
    return true;
}

// Optimized dot product using std::inner_product
template<typename T>
T Vector<T>::dot(const Vector<T>& other) const {
    if (dimension != other.dimension) {
        throw std::invalid_argument("Vector dimensions must match for dot product");
    }
    
    return std::inner_product(data.begin(), data.end(), other.data.begin(), T(0));
}

// Cross product (3D vectors only)
template<typename T>
Vector<T> Vector<T>::cross(const Vector<T>& other) const {
    if (dimension != 3 || other.dimension != 3) {
        throw std::invalid_argument("Cross product is only defined for 3D vectors");
    }
    
    return Vector<T>({
        data[1] * other.data[2] - data[2] * other.data[1],
        data[2] * other.data[0] - data[0] * other.data[2],
        data[0] * other.data[1] - data[1] * other.data[0]
    });
}

// Vector magnitude
template<typename T>
T Vector<T>::magnitude() const {
    return std::sqrt(magnitudeSquared());
}

// Vector magnitude squared (more efficient when you don't need the actual magnitude)
template<typename T>
T Vector<T>::magnitudeSquared() const {
    return std::inner_product(data.begin(), data.end(), data.begin(), T(0));
}

// Normalize vector
template<typename T>
Vector<T> Vector<T>::normalize() const {
    T mag = magnitude();
    if (mag < std::numeric_limits<T>::epsilon()) {
        throw std::runtime_error("Cannot normalize zero vector");
    }
    
    return *this / mag;
}

// Normalize vector in place
template<typename T>
Vector<T>& Vector<T>::normalizeInPlace() {
    T mag = magnitude();
    if (mag < std::numeric_limits<T>::epsilon()) {
        throw std::runtime_error("Cannot normalize zero vector");
    }
    
    *this /= mag;
    return *this;
}

// Distance between vectors
template<typename T>
T Vector<T>::distance(const Vector<T>& other) const {
    return (*this - other).magnitude();
}

// Distance squared between vectors
template<typename T>
T Vector<T>::distanceSquared(const Vector<T>& other) const {
    return (*this - other).magnitudeSquared();
}

// Angle between vectors (in radians)
template<typename T>
T Vector<T>::angle(const Vector<T>& other) const {
    if (dimension != other.dimension) {
        throw std::invalid_argument("Vector dimensions must match for angle calculation");
    }
    
    T dot_product = dot(other);
    T mag_product = magnitude() * other.magnitude();
    
    if (mag_product < std::numeric_limits<T>::epsilon()) {
        throw std::runtime_error("Cannot calculate angle with zero vector");
    }
    
    T cos_angle = dot_product / mag_product;
    // Clamp to [-1, 1] to handle floating point errors
    cos_angle = std::max(T(-1), std::min(T(1), cos_angle));
    
    return std::acos(cos_angle);
}

// Project this vector onto another vector
template<typename T>
Vector<T> Vector<T>::project(const Vector<T>& onto) const {
    if (dimension != onto.dimension) {
        throw std::invalid_argument("Vector dimensions must match for projection");
    }
    
    T onto_mag_sq = onto.magnitudeSquared();
    if (onto_mag_sq < std::numeric_limits<T>::epsilon()) {
        throw std::runtime_error("Cannot project onto zero vector");
    }
    
    T scalar_proj = dot(onto) / onto_mag_sq;
    return onto * scalar_proj;
}

// Reject this vector from another vector (orthogonal component)
template<typename T>
Vector<T> Vector<T>::reject(const Vector<T>& onto) const {
    return *this - project(onto);
}

// Utility functions
template<typename T>
void Vector<T>::fill(const T& value) {
    std::fill(data.begin(), data.end(), value);
}

template<typename T>
void Vector<T>::fillRandom(T min, T max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dis(min, max);
    
    for (auto& element : data) {
        element = dis(gen);
    }
}

template<typename T>
void Vector<T>::resize(size_t newSize, const T& fillValue) {
    data.resize(newSize, fillValue);
    dimension = newSize;
}

template<typename T>
Vector<T> Vector<T>::subVector(size_t start, size_t length) const {
    if (start + length > dimension) {
        throw std::out_of_range("Subvector range exceeds vector bounds");
    }
    
    std::vector<T> sub_data(data.begin() + start, data.begin() + start + length);
    return Vector<T>(sub_data);
}

// Statistical functions
template<typename T>
T Vector<T>::sum() const {
    return std::accumulate(data.begin(), data.end(), T(0));
}

template<typename T>
T Vector<T>::mean() const {
    if (dimension == 0) return T(0);
    return sum() / static_cast<T>(dimension);
}

template<typename T>
T Vector<T>::min() const {
    if (dimension == 0) throw std::runtime_error("Cannot find min of empty vector");
    return *std::min_element(data.begin(), data.end());
}

template<typename T>
T Vector<T>::max() const {
    if (dimension == 0) throw std::runtime_error("Cannot find max of empty vector");
    return *std::max_element(data.begin(), data.end());
}

// Static factory methods
template<typename T>
Vector<T> Vector<T>::zeros(size_t dimension) {
    return Vector<T>(dimension, T(0));
}

template<typename T>
Vector<T> Vector<T>::ones(size_t dimension) {
    return Vector<T>(dimension, T(1));
}

template<typename T>
Vector<T> Vector<T>::random(size_t dimension, T min, T max) {
    Vector<T> result(dimension);
    result.fillRandom(min, max);
    return result;
}

// I/O operations
template<typename T>
void Vector<T>::print(std::ostream& os, int precision) const {
    os << std::fixed << std::setprecision(precision);
    os << "[";
    for (size_t i = 0; i < dimension; ++i) {
        os << data[i];
        if (i < dimension - 1) os << ", ";
    }
    os << "]" << std::endl;
}

template<typename T>
void Vector<T>::readFromInput(std::istream& is) {
    for (size_t i = 0; i < dimension; ++i) {
        std::cout << "Enter component " << i + 1 << ": ";
        is >> data[i];
    }
}

// Friend functions
template<typename T>
Vector<T> operator*(const T& scalar, const Vector<T>& vector) {
    return vector * scalar;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector) {
    vector.print(os);
    return os;
}
