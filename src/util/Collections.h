#pragma once
#include "../engine/Allocator.h"

template<class T>
using AVector = std::vector<T, Allocator<T> >;