#include "Matrix.h"
#include <random>
#include <chrono>

// Addition operator
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    
    Matrix<T> result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// Subtraction operator
template<typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    
    Matrix<T> result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// Optimized matrix multiplication using cache-friendly approach
template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Invalid matrix dimensions for multiplication");
    }
    
    Matrix<T> result(rows, other.cols);
    
    // Cache-friendly blocked matrix multiplication for large matrices
    const size_t BLOCK_SIZE = 64; // Optimal for most modern CPUs
    
    if (rows > BLOCK_SIZE || cols > BLOCK_SIZE || other.cols > BLOCK_SIZE) {
        // Blocked multiplication for large matrices
        for (size_t ii = 0; ii < rows; ii += BLOCK_SIZE) {
            for (size_t jj = 0; jj < other.cols; jj += BLOCK_SIZE) {
                for (size_t kk = 0; kk < cols; kk += BLOCK_SIZE) {
                    // Process block
                    size_t i_end = std::min(ii + BLOCK_SIZE, rows);
                    size_t j_end = std::min(jj + BLOCK_SIZE, other.cols);
                    size_t k_end = std::min(kk + BLOCK_SIZE, cols);
                    
                    for (size_t i = ii; i < i_end; ++i) {
                        for (size_t j = jj; j < j_end; ++j) {
                            T sum = T(0);
                            for (size_t k = kk; k < k_end; ++k) {
                                sum += data[i][k] * other.data[k][j];
                            }
                            result.data[i][j] += sum;
                        }
                    }
                }
            }
        }
    } else {
        // Standard multiplication for smaller matrices
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.cols; ++j) {
                T sum = T(0);
                for (size_t k = 0; k < cols; ++k) {
                    sum += data[i][k] * other.data[k][j];
                }
                result.data[i][j] = sum;
            }
        }
    }
    
    return result;
}

// Scalar multiplication
template<typename T>
Matrix<T> Matrix<T>::operator*(const T& scalar) const {
    Matrix<T> result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

// Addition assignment
template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            data[i][j] += other.data[i][j];
        }
    }
    return *this;
}

// Subtraction assignment
template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            data[i][j] -= other.data[i][j];
        }
    }
    return *this;
}

// Scalar multiplication assignment
template<typename T>
Matrix<T>& Matrix<T>::operator*=(const T& scalar) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            data[i][j] *= scalar;
        }
    }
    return *this;
}

// Equality comparison
template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
    if (rows != other.rows || cols != other.cols) return false;
    
    const T EPSILON = std::numeric_limits<T>::epsilon() * 10;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (std::abs(data[i][j] - other.data[i][j]) > EPSILON) return false;
        }
    }
    return true;
}

// Transpose
template<typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result(cols, rows);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}

// Optimized determinant calculation using LU decomposition for large matrices
template<typename T>
T Matrix<T>::determinant() const {
    if (rows != cols) {
        throw std::invalid_argument("Determinant can only be calculated for square matrices");
    }
    
    if (rows == 1) return data[0][0];
    if (rows == 2) return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    if (rows == 3) {
        return data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1])
             - data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0])
             + data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]);
    }
    
    // Use LU decomposition for larger matrices
    return determinantLU();
}

// LU decomposition based determinant (more efficient for large matrices)
template<typename T>
T Matrix<T>::determinantLU() const {
    Matrix<T> L, U;
    std::tie(L, U) = luDecomposition();
    
    T det = T(1);
    for (size_t i = 0; i < rows; ++i) {
        det *= U.data[i][i];
    }
    
    return det;
}

// LU Decomposition
template<typename T>
std::pair<Matrix<T>, Matrix<T>> Matrix<T>::luDecomposition() const {
    if (rows != cols) {
        throw std::invalid_argument("LU decomposition requires a square matrix");
    }
    
    Matrix<T> L = Matrix<T>::identity(rows);
    Matrix<T> U = *this;
    
    for (size_t k = 0; k < rows - 1; ++k) {
        for (size_t i = k + 1; i < rows; ++i) {
            if (std::abs(U.data[k][k]) < std::numeric_limits<T>::epsilon()) {
                throw std::runtime_error("Matrix is singular - LU decomposition failed");
            }
            
            T factor = U.data[i][k] / U.data[k][k];
            L.data[i][k] = factor;
            
            for (size_t j = k; j < cols; ++j) {
                U.data[i][j] -= factor * U.data[k][j];
            }
        }
    }
    
    return std::make_pair(L, U);
}

// QR Decomposition using Gram-Schmidt process
template<typename T>
std::pair<Matrix<T>, Matrix<T>> Matrix<T>::qrDecomposition() const {
    Matrix<T> Q(rows, cols);
    Matrix<T> R(cols, cols);
    
    // Gram-Schmidt process
    for (size_t j = 0; j < cols; ++j) {
        // Copy column j of A to column j of Q
        for (size_t i = 0; i < rows; ++i) {
            Q.data[i][j] = data[i][j];
        }
        
        // Orthogonalize against previous columns
        for (size_t k = 0; k < j; ++k) {
            T dot_product = T(0);
            for (size_t i = 0; i < rows; ++i) {
                dot_product += Q.data[i][k] * data[i][j];
            }
            R.data[k][j] = dot_product;
            
            for (size_t i = 0; i < rows; ++i) {
                Q.data[i][j] -= dot_product * Q.data[i][k];
            }
        }
        
        // Normalize column j of Q
        T norm = T(0);
        for (size_t i = 0; i < rows; ++i) {
            norm += Q.data[i][j] * Q.data[i][j];
        }
        norm = std::sqrt(norm);
        
        if (norm > std::numeric_limits<T>::epsilon()) {
            R.data[j][j] = norm;
            for (size_t i = 0; i < rows; ++i) {
                Q.data[i][j] /= norm;
            }
        }
    }
    
    return std::make_pair(Q, R);
}

// Matrix inverse using Gauss-Jordan elimination
template<typename T>
Matrix<T> Matrix<T>::inverse() const {
    if (rows != cols) {
        throw std::invalid_argument("Only square matrices can be inverted");
    }
    
    T det = determinant();
    if (std::abs(det) < std::numeric_limits<T>::epsilon()) {
        throw std::runtime_error("Matrix is singular and cannot be inverted");
    }
    
    // Create augmented matrix [A|I]
    Matrix<T> augmented(rows, 2 * cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            augmented.data[i][j] = data[i][j];
            augmented.data[i][j + cols] = (i == j) ? T(1) : T(0);
        }
    }
    
    // Gauss-Jordan elimination
    for (size_t i = 0; i < rows; ++i) {
        // Find pivot
        size_t pivot_row = i;
        for (size_t k = i + 1; k < rows; ++k) {
            if (std::abs(augmented.data[k][i]) > std::abs(augmented.data[pivot_row][i])) {
                pivot_row = k;
            }
        }
        
        // Swap rows if needed
        if (pivot_row != i) {
            for (size_t j = 0; j < 2 * cols; ++j) {
                std::swap(augmented.data[i][j], augmented.data[pivot_row][j]);
            }
        }
        
        // Scale pivot row
        T pivot = augmented.data[i][i];
        for (size_t j = 0; j < 2 * cols; ++j) {
            augmented.data[i][j] /= pivot;
        }
        
        // Eliminate column
        for (size_t k = 0; k < rows; ++k) {
            if (k != i) {
                T factor = augmented.data[k][i];
                for (size_t j = 0; j < 2 * cols; ++j) {
                    augmented.data[k][j] -= factor * augmented.data[i][j];
                }
            }
        }
    }
    
    // Extract inverse matrix
    Matrix<T> result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result.data[i][j] = augmented.data[i][j + cols];
        }
    }
    
    return result;
}

// Trace (sum of diagonal elements)
template<typename T>
T Matrix<T>::trace() const {
    if (rows != cols) {
        throw std::invalid_argument("Trace can only be calculated for square matrices");
    }
    
    T tr = T(0);
    for (size_t i = 0; i < rows; ++i) {
        tr += data[i][i];
    }
    return tr;
}

// Eigenvalue computation for symmetric matrices using QR algorithm
template<typename T>
std::vector<std::complex<T>> Matrix<T>::eigenvalues() const {
    if (rows != cols) {
        throw std::invalid_argument("Eigenvalues can only be calculated for square matrices");
    }
    
    if (rows == 1) {
        return {std::complex<T>(data[0][0], 0)};
    }
    
    if (rows == 2) {
        T a = data[0][0];
        T b = data[0][1];
        T c = data[1][0];
        T d = data[1][1];
        
        T trace = a + d;
        T det = a * d - b * c;
        T discriminant = trace * trace - 4 * det;
        
        std::vector<std::complex<T>> eigenvals;
        if (discriminant >= 0) {
            T sqrt_disc = std::sqrt(discriminant);
            eigenvals.push_back(std::complex<T>((trace + sqrt_disc) / 2, 0));
            eigenvals.push_back(std::complex<T>((trace - sqrt_disc) / 2, 0));
        } else {
            T sqrt_disc = std::sqrt(-discriminant);
            eigenvals.push_back(std::complex<T>(trace / 2, sqrt_disc / 2));
            eigenvals.push_back(std::complex<T>(trace / 2, -sqrt_disc / 2));
        }
        return eigenvals;
    }
    
    // For larger matrices, use QR algorithm
    Matrix<T> A = *this;
    const int MAX_ITERATIONS = 1000;
    const T TOLERANCE = std::numeric_limits<T>::epsilon() * 100;
    
    std::vector<std::complex<T>> eigenvals;
    
    for (int iter = 0; iter < MAX_ITERATIONS; ++iter) {
        auto [Q, R] = A.qrDecomposition();
        A = R * Q;
        
        // Check for convergence (simplified check)
        T off_diagonal_sum = T(0);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (i != j) {
                    off_diagonal_sum += std::abs(A.data[i][j]);
                }
            }
        }
        
        if (off_diagonal_sum < TOLERANCE) {
            break;
        }
    }
    
    // Extract eigenvalues from diagonal
    for (size_t i = 0; i < rows; ++i) {
        eigenvals.push_back(std::complex<T>(A.data[i][i], 0));
    }
    
    return eigenvals;
}

// Utility functions
template<typename T>
void Matrix<T>::fill(const T& value) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            data[i][j] = value;
        }
    }
}

template<typename T>
void Matrix<T>::fillRandom(T min, T max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dis(min, max);
    
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            data[i][j] = dis(gen);
        }
    }
}

// Static factory methods
template<typename T>
Matrix<T> Matrix<T>::identity(size_t n) {
    Matrix<T> result(n, n);
    for (size_t i = 0; i < n; ++i) {
        result.data[i][i] = T(1);
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::zeros(size_t rows, size_t cols) {
    return Matrix<T>(rows, cols, T(0));
}

template<typename T>
Matrix<T> Matrix<T>::ones(size_t rows, size_t cols) {
    return Matrix<T>(rows, cols, T(1));
}

template<typename T>
Matrix<T> Matrix<T>::random(size_t rows, size_t cols, T min, T max) {
    Matrix<T> result(rows, cols);
    result.fillRandom(min, max);
    return result;
}

// I/O operations
template<typename T>
void Matrix<T>::print(std::ostream& os, int precision) const {
    os << std::fixed << std::setprecision(precision);
    for (size_t i = 0; i < rows; ++i) {
        os << "[";
        for (size_t j = 0; j < cols; ++j) {
            os << std::setw(precision + 4) << data[i][j];
            if (j < cols - 1) os << " ";
        }
        os << "]" << std::endl;
    }
}

template<typename T>
void Matrix<T>::readFromInput(std::istream& is) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << "Enter element [" << i + 1 << "][" << j + 1 << "]: ";
            is >> data[i][j];
        }
    }
}

// Friend functions
template<typename T>
Matrix<T> operator*(const T& scalar, const Matrix<T>& matrix) {
    return matrix * scalar;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    matrix.print(os);
    return os;
}
