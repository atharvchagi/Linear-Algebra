#include "Matrix.h"
#include "Vector.h"
#include "PerformanceBenchmark.h"
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>

void displayMenu() {
    std::cout << "===============================================" << std::endl;
    std::cout << "   HIGH-PERFORMANCE LINEAR ALGEBRA LIBRARY" << std::endl;
    std::cout << "            by Atharv Chagi" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "1. Matrix Multiplication Calculator" << std::endl;
    std::cout << "2. Determinant Calculator" << std::endl;
    std::cout << "3. Eigenvalue Calculator" << std::endl;
    std::cout << "4. Matrix Inverse Calculator" << std::endl;
    std::cout << "5. Vector Dot Product Calculator" << std::endl;
    std::cout << "6. Vector Cross Product Calculator" << std::endl;
    std::cout << "7. LU Decomposition" << std::endl;
    std::cout << "8. QR Decomposition" << std::endl;
    std::cout << "9. Performance Benchmark Suite" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter your choice: ";
}

void matrixMultiplicationCalculator() {
    std::cout << "\n--- Matrix Multiplication Calculator ---" << std::endl;
    
    size_t rows1, cols1, rows2, cols2;
    
    std::cout << "Enter dimensions for Matrix A (rows cols): ";
    std::cin >> rows1 >> cols1;
    
    std::cout << "Enter dimensions for Matrix B (rows cols): ";
    std::cin >> rows2 >> cols2;
    
    if (cols1 != rows2) {
        std::cout << "Error: Invalid dimensions for multiplication!" << std::endl;
        std::cout << "Matrix A columns (" << cols1 << ") must equal Matrix B rows (" << rows2 << ")" << std::endl;
        return;
    }
    
    MatrixD matrixA(rows1, cols1);
    MatrixD matrixB(rows2, cols2);
    
    std::cout << "\nEnter Matrix A:" << std::endl;
    matrixA.readFromInput();
    
    std::cout << "\nEnter Matrix B:" << std::endl;
    matrixB.readFromInput();
    
    std::cout << "\nMatrix A:" << std::endl;
    matrixA.print();
    
    std::cout << "\nMatrix B:" << std::endl;
    matrixB.print();
    
    auto start = std::chrono::high_resolution_clock::now();
    MatrixD result = matrixA * matrixB;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "\nResult (A × B):" << std::endl;
    result.print();
    
    std::cout << "\nComputation time: " << duration.count() << " microseconds" << std::endl;
}

void determinantCalculator() {
    std::cout << "\n--- Determinant Calculator ---" << std::endl;
    
    size_t size;
    std::cout << "Enter matrix size (n x n): ";
    std::cin >> size;
    
    MatrixD matrix(size, size);
    
    std::cout << "\nEnter matrix elements:" << std::endl;
    matrix.readFromInput();
    
    std::cout << "\nMatrix:" << std::endl;
    matrix.print();
    
    auto start = std::chrono::high_resolution_clock::now();
    double det = matrix.determinant();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "\nDeterminant: " << std::fixed << std::setprecision(6) << det << std::endl;
    std::cout << "Computation time: " << duration.count() << " microseconds" << std::endl;
}

void eigenvalueCalculator() {
    std::cout << "\n--- Eigenvalue Calculator ---" << std::endl;
    
    size_t size;
    std::cout << "Enter matrix size (n x n): ";
    std::cin >> size;
    
    MatrixD matrix(size, size);
    
    std::cout << "\nEnter matrix elements:" << std::endl;
    matrix.readFromInput();
    
    std::cout << "\nMatrix:" << std::endl;
    matrix.print();
    
    auto start = std::chrono::high_resolution_clock::now();
    auto eigenvals = matrix.eigenvalues();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "\nEigenvalues:" << std::endl;
    for (size_t i = 0; i < eigenvals.size(); ++i) {
        if (std::abs(eigenvals[i].imag()) < 1e-10) {
            std::cout << "λ" << i+1 << " = " << std::fixed << std::setprecision(6) << eigenvals[i].real() << std::endl;
        } else {
            std::cout << "λ" << i+1 << " = " << std::fixed << std::setprecision(6) 
                      << eigenvals[i].real() << " + " << eigenvals[i].imag() << "i" << std::endl;
        }
    }
    
    std::cout << "\nComputation time: " << duration.count() << " microseconds" << std::endl;
}

void matrixInverseCalculator() {
    std::cout << "\n--- Matrix Inverse Calculator ---" << std::endl;
    
    size_t size;
    std::cout << "Enter matrix size (n x n): ";
    std::cin >> size;
    
    MatrixD matrix(size, size);
    
    std::cout << "\nEnter matrix elements:" << std::endl;
    matrix.readFromInput();
    
    std::cout << "\nMatrix:" << std::endl;
    matrix.print();
    
    try {
        auto start = std::chrono::high_resolution_clock::now();
        MatrixD inverse = matrix.inverse();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "\nInverse Matrix:" << std::endl;
        inverse.print();
        
        // Verify by multiplication
        MatrixD verification = matrix * inverse;
        std::cout << "\nVerification (A × A⁻¹):" << std::endl;
        verification.print();
        
        std::cout << "\nComputation time: " << duration.count() << " microseconds" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\nError: " << e.what() << std::endl;
    }
}

void vectorDotProductCalculator() {
    std::cout << "\n--- Vector Dot Product Calculator ---" << std::endl;
    
    size_t dimension;
    std::cout << "Enter vector dimension: ";
    std::cin >> dimension;
    
    VectorD vector1(dimension);
    VectorD vector2(dimension);
    
    std::cout << "\nEnter Vector 1:" << std::endl;
    vector1.readFromInput();
    
    std::cout << "\nEnter Vector 2:" << std::endl;
    vector2.readFromInput();
    
    std::cout << "\nVector 1: ";
    vector1.print();
    
    std::cout << "Vector 2: ";
    vector2.print();
    
    auto start = std::chrono::high_resolution_clock::now();
    double dotProduct = vector1.dot(vector2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "\nDot Product: " << std::fixed << std::setprecision(6) << dotProduct << std::endl;
    std::cout << "Computation time: " << duration.count() << " nanoseconds" << std::endl;
    
    // Additional vector operations
    std::cout << "\nAdditional Information:" << std::endl;
    std::cout << "Vector 1 magnitude: " << vector1.magnitude() << std::endl;
    std::cout << "Vector 2 magnitude: " << vector2.magnitude() << std::endl;
    std::cout << "Angle between vectors: " << vector1.angle(vector2) << " radians" << std::endl;
}

void vectorCrossProductCalculator() {
    std::cout << "\n--- Vector Cross Product Calculator ---" << std::endl;
    std::cout << "Note: Cross product is only defined for 3D vectors" << std::endl;
    
    VectorD vector1(3);
    VectorD vector2(3);
    
    std::cout << "\nEnter Vector 1 (3D):" << std::endl;
    vector1.readFromInput();
    
    std::cout << "\nEnter Vector 2 (3D):" << std::endl;
    vector2.readFromInput();
    
    std::cout << "\nVector 1: ";
    vector1.print();
    
    std::cout << "Vector 2: ";
    vector2.print();
    
    auto start = std::chrono::high_resolution_clock::now();
    VectorD crossProduct = vector1.cross(vector2);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "\nCross Product: ";
    crossProduct.print();
    
    std::cout << "\nComputation time: " << duration.count() << " nanoseconds" << std::endl;
    
    // Additional information
    std::cout << "\nAdditional Information:" << std::endl;
    std::cout << "Cross product magnitude: " << crossProduct.magnitude() << std::endl;
    std::cout << "Area of parallelogram: " << crossProduct.magnitude() << std::endl;
}

void luDecomposition() {
    std::cout << "\n--- LU Decomposition ---" << std::endl;
    
    size_t size;
    std::cout << "Enter matrix size (n x n): ";
    std::cin >> size;
    
    MatrixD matrix(size, size);
    
    std::cout << "\nEnter matrix elements:" << std::endl;
    matrix.readFromInput();
    
    std::cout << "\nOriginal Matrix:" << std::endl;
    matrix.print();
    
    try {
        auto start = std::chrono::high_resolution_clock::now();
        auto [L, U] = matrix.luDecomposition();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "\nL Matrix (Lower Triangular):" << std::endl;
        L.print();
        
        std::cout << "\nU Matrix (Upper Triangular):" << std::endl;
        U.print();
        
        // Verify decomposition
        MatrixD verification = L * U;
        std::cout << "\nVerification (L × U):" << std::endl;
        verification.print();
        
        std::cout << "\nComputation time: " << duration.count() << " microseconds" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\nError: " << e.what() << std::endl;
    }
}

void qrDecomposition() {
    std::cout << "\n--- QR Decomposition ---" << std::endl;
    
    size_t rows, cols;
    std::cout << "Enter matrix dimensions (rows cols): ";
    std::cin >> rows >> cols;
    
    MatrixD matrix(rows, cols);
    
    std::cout << "\nEnter matrix elements:" << std::endl;
    matrix.readFromInput();
    
    std::cout << "\nOriginal Matrix:" << std::endl;
    matrix.print();
    
    auto start = std::chrono::high_resolution_clock::now();
    auto [Q, R] = matrix.qrDecomposition();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "\nQ Matrix (Orthogonal):" << std::endl;
    Q.print();
    
    std::cout << "\nR Matrix (Upper Triangular):" << std::endl;
    R.print();
    
    // Verify decomposition
    MatrixD verification = Q * R;
    std::cout << "\nVerification (Q × R):" << std::endl;
    verification.print();
    
    std::cout << "\nComputation time: " << duration.count() << " microseconds" << std::endl;
}

int main() {
    int choice;
    
    do {
        displayMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                matrixMultiplicationCalculator();
                break;
            case 2:
                determinantCalculator();
                break;
            case 3:
                eigenvalueCalculator();
                break;
            case 4:
                matrixInverseCalculator();
                break;
            case 5:
                vectorDotProductCalculator();
                break;
            case 6:
                vectorCrossProductCalculator();
                break;
            case 7:
                luDecomposition();
                break;
            case 8:
                qrDecomposition();
                break;
            case 9:
                PerformanceBenchmark::runFullBenchmarkSuite();
                break;
            case 0:
                std::cout << "\nThank you for using the High-Performance Linear Algebra Library!" << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice! Please try again." << std::endl;
        }
        
        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            std::cout << "\n";
        }
        
    } while (choice != 0);
    
    return 0;
}
