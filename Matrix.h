#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <complex>
#include <memory>

template<typename T = double>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    // Constructors
    Matrix() : rows(0), cols(0) {}
    Matrix(size_t r, size_t c) : rows(r), cols(c), data(r, std::vector<T>(c, T(0))) {}
    Matrix(size_t r, size_t c, const T& value) : rows(r), cols(c), data(r, std::vector<T>(c, value)) {}
    Matrix(const std::vector<std::vector<T>>& mat) : data(mat), rows(mat.size()), cols(mat.empty() ? 0 : mat[0].size()) {}
    
    // Copy constructor and assignment operator
    Matrix(const Matrix& other) = default;
    Matrix& operator=(const Matrix& other) = default;
    
    // Move constructor and assignment operator
    Matrix(Matrix&& other) noexcept = default;
    Matrix& operator=(Matrix&& other) noexcept = default;
    
    // Destructor
    ~Matrix() = default;

    // Accessors
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    
    // Element access
    T& operator()(size_t i, size_t j) {
        if (i >= rows || j >= cols) throw std::out_of_range("Matrix indices out of range");
        return data[i][j];
    }
    
    const T& operator()(size_t i, size_t j) const {
        if (i >= rows || j >= cols) throw std::out_of_range("Matrix indices out of range");
        return data[i][j];
    }
    
    // Row access
    std::vector<T>& operator[](size_t i) {
        if (i >= rows) throw std::out_of_range("Row index out of range");
        return data[i];
    }
    
    const std::vector<T>& operator[](size_t i) const {
        if (i >= rows) throw std::out_of_range("Row index out of range");
        return data[i];
    }

    // Basic operations
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(const T& scalar) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const T& scalar);
    
    // Comparison
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const { return !(*this == other); }

    // Matrix operations
    Matrix transpose() const;
    T determinant() const;
    Matrix inverse() const;
    T trace() const;
    Matrix adjugate() const;
    
    // Eigenvalue decomposition (for symmetric matrices)
    std::pair<std::vector<T>, Matrix> eigenDecomposition() const;
    std::vector<std::complex<T>> eigenvalues() const;
    
    // LU Decomposition
    std::pair<Matrix, Matrix> luDecomposition() const;
    
    // QR Decomposition
    std::pair<Matrix, Matrix> qrDecomposition() const;
    
    // Utility functions
    void fill(const T& value);
    void fillRandom(T min = T(0), T max = T(1));
    Matrix subMatrix(size_t startRow, size_t endRow, size_t startCol, size_t endCol) const;
    void resize(size_t newRows, size_t newCols, const T& fillValue = T(0));
    
    // Static factory methods
    static Matrix identity(size_t n);
    static Matrix zeros(size_t rows, size_t cols);
    static Matrix ones(size_t rows, size_t cols);
    static Matrix random(size_t rows, size_t cols, T min = T(0), T max = T(1));
    
    // I/O operations
    void print(std::ostream& os = std::cout, int precision = 6) const;
    void readFromInput(std::istream& is = std::cin);
    
    // Friends
    template<typename U>
    friend Matrix<U> operator*(const U& scalar, const Matrix<U>& matrix);
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix);

private:
    // Helper functions for advanced operations
    T determinantLU() const;
    T determinantRecursive() const;
    Matrix gaussianElimination() const;
    void swapRows(size_t i, size_t j);
    void scaleRow(size_t i, const T& factor);
    void addScaledRow(size_t target, size_t source, const T& factor);
    
    // Eigenvalue computation helpers
    void householderReduction(Matrix& Q, Matrix& H) const;
    std::vector<T> qrAlgorithm(Matrix tridiagonal) const;
};

// Typedef for common types
using MatrixD = Matrix<double>;
using MatrixF = Matrix<float>;
using MatrixI = Matrix<int>;

#include "Matrix.cpp"  // Include implementation for template class
