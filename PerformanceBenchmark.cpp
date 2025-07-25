#include "PerformanceBenchmark.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

void PerformanceBenchmark::benchmarkMatrixMultiplication() {
    printHeader("Matrix Multiplication Benchmark");
    
    std::vector<size_t> sizes = {10, 50, 100, 200, 500, 1000};
    
    for (size_t size : sizes) {
        auto matA = generateRandomMatrix(size);
        auto matB = generateRandomMatrix(size);
        
        std::string desc = "Matrix multiplication " + std::to_string(size) + "x" + std::to_string(size);
        double time = timeFunction(desc, [&]() {
            auto result = matA * matB;
        });
        
        double ops = 2.0 * size * size * size; // Number of operations
        double gflops = ops / (time * 1e6); // GFLOPS
        
        printResult(desc, time, std::to_string(gflops) + " GFLOPS");
    }
}

void PerformanceBenchmark::benchmarkDeterminant() {
    printHeader("Determinant Calculation Benchmark");
    
    std::vector<size_t> sizes = {5, 10, 20, 50, 100, 200};
    
    for (size_t size : sizes) {
        auto matrix = generateRandomMatrix(size);
        
        std::string desc = "Determinant " + std::to_string(size) + "x" + std::to_string(size);
        double time = timeFunction(desc, [&]() {
            auto det = matrix.determinant();
        });
        
        printResult(desc, time);
    }
}

void PerformanceBenchmark::benchmarkEigenvalues() {
    printHeader("Eigenvalue Calculation Benchmark");
    
    std::vector<size_t> sizes = {5, 10, 20, 50, 100};
    
    for (size_t size : sizes) {
        auto matrix = generateRandomMatrix(size);
        
        std::string desc = "Eigenvalues " + std::to_string(size) + "x" + std::to_string(size);
        double time = timeFunction(desc, [&]() {
            auto eigenvals = matrix.eigenvalues();
        });
        
        printResult(desc, time);
    }
}

void PerformanceBenchmark::benchmarkInverse() {
    printHeader("Matrix Inverse Benchmark");
    
    std::vector<size_t> sizes = {5, 10, 20, 50, 100, 200};
    
    for (size_t size : sizes) {
        auto matrix = generateRandomMatrix(size);
        // Make sure matrix is invertible by adding identity matrix
        auto identity = MatrixD::identity(size);
        matrix = matrix + identity * 0.1;
        
        std::string desc = "Matrix inverse " + std::to_string(size) + "x" + std::to_string(size);
        double time = timeFunction(desc, [&]() {
            auto inv = matrix.inverse();
        });
        
        printResult(desc, time);
    }
}

void PerformanceBenchmark::benchmarkLUDecomposition() {
    printHeader("LU Decomposition Benchmark");
    
    std::vector<size_t> sizes = {10, 50, 100, 200, 500};
    
    for (size_t size : sizes) {
        auto matrix = generateRandomMatrix(size);
        
        std::string desc = "LU Decomposition " + std::to_string(size) + "x" + std::to_string(size);
        double time = timeFunction(desc, [&]() {
            auto [L, U] = matrix.luDecomposition();
        });
        
        printResult(desc, time);
    }
}

void PerformanceBenchmark::benchmarkQRDecomposition() {
    printHeader("QR Decomposition Benchmark");
    
    std::vector<size_t> sizes = {10, 50, 100, 200};
    
    for (size_t size : sizes) {
        auto matrix = generateRandomMatrix(size);
        
        std::string desc = "QR Decomposition " + std::to_string(size) + "x" + std::to_string(size);
        double time = timeFunction(desc, [&]() {
            auto [Q, R] = matrix.qrDecomposition();
        });
        
        printResult(desc, time);
    }
}

void PerformanceBenchmark::benchmarkVectorOperations() {
    printHeader("Vector Operations Benchmark");
    
    std::vector<size_t> sizes = {1000, 10000, 100000, 1000000};
    
    for (size_t size : sizes) {
        auto vecA = generateRandomVector(size);
        auto vecB = generateRandomVector(size);
        
        // Vector addition
        std::string desc = "Vector addition (size " + std::to_string(size) + ")";
        double time = timeFunction(desc, [&]() {
            auto result = vecA + vecB;
        });
        printResult(desc, time);
        
        // Vector magnitude
        desc = "Vector magnitude (size " + std::to_string(size) + ")";
        time = timeFunction(desc, [&]() {
            auto mag = vecA.magnitude();
        });
        printResult(desc, time);
        
        // Vector normalization
        desc = "Vector normalization (size " + std::to_string(size) + ")";
        time = timeFunction(desc, [&]() {
            auto normalized = vecA.normalize();
        });
        printResult(desc, time);
    }
}

void PerformanceBenchmark::benchmarkDotProduct() {
    printHeader("Dot Product Benchmark");
    
    std::vector<size_t> sizes = {1000, 10000, 100000, 1000000, 10000000};
    
    for (size_t size : sizes) {
        auto vecA = generateRandomVector(size);
        auto vecB = generateRandomVector(size);
        
        std::string desc = "Dot product (size " + std::to_string(size) + ")";
        double time = timeFunction(desc, [&]() {
            auto dot = vecA.dot(vecB);
        });
        
        double ops = static_cast<double>(size) * 2; // multiply and add for each element
        double gflops = ops / (time * 1e6);
        
        printResult(desc, time, std::to_string(gflops) + " GFLOPS");
    }
}

void PerformanceBenchmark::benchmarkCrossProduct() {
    printHeader("Cross Product Benchmark");
    
    const size_t NUM_OPERATIONS = 10000000;
    
    auto vecA = VectorD({1.0, 2.0, 3.0});
    auto vecB = VectorD({4.0, 5.0, 6.0});
    
    std::string desc = "Cross product (" + std::to_string(NUM_OPERATIONS) + " operations)";
    double time = timeFunction(desc, [&]() {
        for (size_t i = 0; i < NUM_OPERATIONS; ++i) {
            auto cross = vecA.cross(vecB);
        }
    });
    
    double ops_per_second = NUM_OPERATIONS / (time / 1000.0);
    printResult(desc, time, std::to_string(ops_per_second) + " ops/sec");
}

void PerformanceBenchmark::runFullBenchmarkSuite() {
    std::cout << "========================================" << std::endl;
    std::cout << "  HIGH-PERFORMANCE LINEAR ALGEBRA LIBRARY" << std::endl;
    std::cout << "           BENCHMARK SUITE" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    benchmarkMatrixMultiplication();
    std::cout << std::endl;
    
    benchmarkDeterminant();
    std::cout << std::endl;
    
    benchmarkEigenvalues();
    std::cout << std::endl;
    
    benchmarkInverse();
    std::cout << std::endl;
    
    benchmarkLUDecomposition();
    std::cout << std::endl;
    
    benchmarkQRDecomposition();
    std::cout << std::endl;
    
    benchmarkVectorOperations();
    std::cout << std::endl;
    
    benchmarkDotProduct();
    std::cout << std::endl;
    
    benchmarkCrossProduct();
    std::cout << std::endl;
    
    testAccuracy();
    
    std::cout << "========================================" << std::endl;
    std::cout << "        BENCHMARK SUITE COMPLETE" << std::endl;
    std::cout << "========================================" << std::endl;
}

void PerformanceBenchmark::analyzeMemoryUsage() {
    printHeader("Memory Usage Analysis");
    
    std::vector<size_t> sizes = {100, 500, 1000};
    
    for (size_t size : sizes) {
        size_t matrix_memory = size * size * sizeof(double);
        size_t vector_memory = size * sizeof(double);
        
        std::cout << "Matrix " << size << "x" << size << ": " 
                  << matrix_memory / 1024.0 / 1024.0 << " MB" << std::endl;
        std::cout << "Vector " << size << ": " 
                  << vector_memory / 1024.0 << " KB" << std::endl;
    }
}

void PerformanceBenchmark::testAccuracy() {
    printHeader("Accuracy Tests");
    
    // Test matrix multiplication accuracy
    MatrixD A({{1, 2}, {3, 4}});
    MatrixD B({{5, 6}, {7, 8}});
    MatrixD expected({{19, 22}, {43, 50}});
    MatrixD result = A * B;
    
    bool mult_correct = (result == expected);
    std::cout << "Matrix multiplication accuracy: " << (mult_correct ? "PASS" : "FAIL") << std::endl;
    
    // Test determinant accuracy
    MatrixD det_test({{1, 2}, {3, 4}});
    double det_result = det_test.determinant();
    double det_expected = -2.0;
    bool det_correct = std::abs(det_result - det_expected) < 1e-10;
    std::cout << "Determinant accuracy: " << (det_correct ? "PASS" : "FAIL") << std::endl;
    
    // Test dot product accuracy
    VectorD v1({1, 2, 3});
    VectorD v2({4, 5, 6});
    double dot_result = v1.dot(v2);
    double dot_expected = 32.0; // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
    bool dot_correct = std::abs(dot_result - dot_expected) < 1e-10;
    std::cout << "Dot product accuracy: " << (dot_correct ? "PASS" : "FAIL") << std::endl;
    
    // Test cross product accuracy
    VectorD cross_result = v1.cross(v2);
    VectorD cross_expected({-3, 6, -3}); // [2*6-3*5, 3*4-1*6, 1*5-2*4] = [-3, 6, -3]
    bool cross_correct = (cross_result == cross_expected);
    std::cout << "Cross product accuracy: " << (cross_correct ? "PASS" : "FAIL") << std::endl;
    
    // Test inverse accuracy
    MatrixD inv_test = MatrixD::identity(3);
    inv_test(0, 1) = 2.0;
    MatrixD inv_result = inv_test.inverse();
    MatrixD identity_check = inv_test * inv_result;
    MatrixD identity_expected = MatrixD::identity(3);
    bool inv_correct = (identity_check == identity_expected);
    std::cout << "Matrix inverse accuracy: " << (inv_correct ? "PASS" : "FAIL") << std::endl;
}

void PerformanceBenchmark::printHeader(const std::string& title) {
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void PerformanceBenchmark::printResult(const std::string& operation, double time_ms, const std::string& additional_info) {
    std::cout << std::left << std::setw(40) << operation 
              << std::right << std::setw(10) << std::fixed << std::setprecision(3) << time_ms << " ms";
    if (!additional_info.empty()) {
        std::cout << " (" << additional_info << ")";
    }
    std::cout << std::endl;
}

MatrixD PerformanceBenchmark::generateRandomMatrix(size_t size) {
    MatrixD matrix(size, size);
    matrix.fillRandom(-10.0, 10.0);
    return matrix;
}

VectorD PerformanceBenchmark::generateRandomVector(size_t size) {
    VectorD vector(size);
    vector.fillRandom(-10.0, 10.0);
    return vector;
}
