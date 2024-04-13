#pragma once
#include <vector>
#include <functional>
#include <algorithm>

class VectorExtensions
{
public:
	template <typename T>
	static void forEach(std::vector<T> vector, std::function<void(const T&)> operation);
};

template<typename T>
inline void VectorExtensions::forEach(std::vector<T> vector, std::function<void(const T&)> operation)
{
	std::for_each(std::begin(vector), std::end(vector), operation);
}
