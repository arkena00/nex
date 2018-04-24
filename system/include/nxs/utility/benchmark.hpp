#ifndef UTILITY_BENCHMARK_H_NXS
#define UTILITY_BENCHMARK_H_NXS

#include <chrono>
#include <iostream>

#define BENCHMARK_BEGIN_IMPL(NAME, ITERATION, ...) \
    std::chrono::time_point<std::chrono::high_resolution_clock> NAME##_benchmark_clock_begin, NAME##_benchmark_clock_end; \
    NAME##_benchmark_clock_begin = std::chrono::high_resolution_clock::now(); \
    std::string NAME##_benchmark_name = #NAME; \
    int NAME##_benchmark_iterator = 0; \
    int NAME##_benchmark_iterator_end = ITERATION; \
    do { NAME##_benchmark_iterator++; \

#define BENCHMARK_END(NAME) \
    } while (NAME##_benchmark_iterator < NAME##_benchmark_iterator_end); \
    NAME##_benchmark_clock_end = std::chrono::high_resolution_clock::now(); \
    auto NAME##_benchmark_duration = std::chrono::duration<float, std::chrono::milliseconds::period>(NAME##_benchmark_clock_end - NAME##_benchmark_clock_begin).count(); \
    NAME##_benchmark_duration /= NAME##_benchmark_iterator_end; \
    std::cout << "\n********************** BENCHMARK : " << NAME##_benchmark_name << "\n"; \
    std::cout << "\n average duration : " << NAME##_benchmark_duration << " ms \n iteration : " << NAME##_benchmark_iterator_end; \
    std::cout << "\n\n**********************\n\n";

#define BENCHMARK_BEGIN(...) BENCHMARK_BEGIN_IMPL(__VA_ARGS__, 1)

#endif // UTILITY_BENCHMARK_H_NXS
