#pragma once
#include <memory>

template <typename T>
class Allocator : public std::allocator<T>
{
public:
	T* allocate(size_type n, const void *hint = 0)
	{
		return std::allocator<T>::allocate(n, hint);
	}

	void deallocate(T* p, size_type n)
	{
		return std::allocator<T>::deallocate(p, n);
	}
};

