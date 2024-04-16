#pragma once
#include <tuple>

template <typename T, typename... Types>
class GameObjectToInstantiate
{
public:
	GameObjectToInstantiate(T&& gameObjectType, Types&&... arguments)
		:
		gameObjectType{ std::forward(gameObjectType) },
		arguments{ std::forward(arguments) }
	{
	}

	T gameObjectType;
	std::tuple<Types...> arguments;
};

