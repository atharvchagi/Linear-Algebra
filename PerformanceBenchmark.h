#pragma once
#include "Matrix.h"
#include "Vector.h"
#include <chrono>
#include <functional>
#include <string>
#include <iomanip>

class PerformanceBenchmark {
private:
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    using Duration = std::chrono::duration<double, std::milli>;

public:
    // Benchmark matrix operations
    static void benchmarkMatrixMultiplication();
    static void benchmarkDeterminant();
    static void benchmarkEigenvalues();
    static void benchmarkInverse();
    static void benchmarkLUDecomposition();
    static void benchmarkQRDecomposition();
    
    // Benchmark vector operations
    static void benchmarkVectorOperations();
    static void benchmarkDotProduct();
    static void benchmarkCrossProduct();
    
    // Comprehensive benchmark suite
    static void runFullBenchmarkSuite();
    
    // Memory usage analysis
    static void analyzeMemoryUsage();
    
    // Accuracy tests
    static void testAccuracy();

private:
    // Utility functions
    template<typename Func>
    static double timeFunction(const std::string& description, Func&& func);
    
    static void printHeader(const std::string& title);
    static void printResult(const std::string& operation, double time_ms, const std::string& additional_info = "");
    
    // Test data generators
    static MatrixD generateRandomMatrix(size_t size);
    static VectorD generateRandomVector(size_t size);
};

template<typename Func>
double PerformanceBenchmark::timeFunction(const std::string& description, Func&& func) {
    std::cout << "Running: " << description << "... " << std::flush;
    
    auto start = Clock::now();
    func();
    auto end = Clock::now();
    
    double elapsed = Duration(end - start).count();
    std::cout << "Done (" << std::fixed << std::setprecision(3) << elapsed << " ms)" << std::endl;
    
    return elapsed;
}
