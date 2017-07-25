#pragma once
#include "../external/loguru.hpp"
#include <string>
std::string CreateCategoryString(const char* category, const char* msg);

#define LOGGING_LEVEL_1
#if defined(LOGGING_LEVEL_1)
#define LOG_L1(Category, Severity, FRMT, ...) LOG_F(Severity, CreateCategoryString(#Category, #FRMT).c_str(), __VA_ARGS__)
#define LOG_L2(Category, Severity, FRMT, ...)
#define LOG_L3(Category, Severity, FRMT, ...)
#elif defined(LOGGING_LEVEL_2)
#define LOG_L1(Category, Severity, FRMT, ...) LOG_F(Severity, CreateCategoryString(#Category, #FRMT).c_str(), __VA_ARGS__)
#define LOG_L2(Category, Severity, FRMT, ...) LOG_F(Severity, CreateCategoryString(#Category, #FRMT).c_str(), __VA_ARGS__)
#define LOG_L3(Category, Severity, FRMT, ...)
#elif defined(LOGGING_LEVEL_3)
#define LOG_L1(Category, Severity, FRMT, ...) LOG_F(Severity, CreateCategoryString(#Category, #FRMT).c_str(), __VA_ARGS__)
#define LOG_L2(Category, Severity, FRMT, ...) LOG_F(Severity, CreateCategoryString(#Category, #FRMT).c_str(), __VA_ARGS__)
#define LOG_L3(Category, Severity, FRMT, ...) LOG_F(Severity, CreateCategoryString(#Category, #FRMT).c_str(), __VA_ARGS__)
#endif