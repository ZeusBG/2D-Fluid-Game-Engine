#pragma once
#include "../engine/Allocator.h"
#include <vector>

template<class T>
using AVector = std::vector<T, Allocator<T> >;