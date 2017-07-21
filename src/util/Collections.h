#pragma once
#include "../engine/memory/Allocator.h"
#include <vector>

template<class T>
using AVector = std::vector<T, Allocator<T> >;