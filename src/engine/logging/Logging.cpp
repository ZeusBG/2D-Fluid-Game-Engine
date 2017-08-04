#pragma once
#include "Logging.h"
#define LOGURU_IMPLEMENTATION 1
#include "../extern/loguru/loguru.hpp"
#include <sstream>

std::string CreateCategoryString(const char* category, const char* msg)
{
	std::ostringstream stringStream;
	stringStream << "Category: " << category << " |  Message: " << msg << '\n';
	return stringStream.str();
}