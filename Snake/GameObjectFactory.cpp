#include "GameObjectFactory.h"
#include "BoxCollider.h"

GameObjectFactory::GameObjectFactory(TextureStore textureStore, GameObjectStore& gameObjectStore)
	:
	textureStore{ textureStore },
	gameObjectStore{ gameObjectStore }
{
}

Snake* GameObjectFactory::createSnake()
{
	float snakePartSize{ 20.f };
	size_t snakePartCount{ 2 };

	auto turnPointStore{ std::make_unique<TurnPointStore>() };
	GeneratorOfSnakePartPositions generatorOfSnakePartPositions{ turnPointStore.get(), snakePartCount, snakePartSize };

	auto snake = std::make_unique<Snake>(std::move(turnPointStore), generatorOfSnakePartPositions);

	auto transform{ snake->addComponent<Transform>() };
	transform->setForward({ 1.f, 0.f });
	transform->setPosition({ 300.f, 150.f });

	snake->addComponent<SnakeMovement>(transform, 5.f);

	sf::Sprite sprite{};
	sprite.setOrigin({ snakePartSize / 2.f, snakePartSize / 2.f });
	sprite.setTexture(textureStore.getTestTexture());

	for (size_t i = 0; i < snakePartCount; i++)
	{
		snake->addComponent<MeshRenderer>(sprite);
		snake->addComponent<BoxCollider>(transform, sf::Vector2f{}, sf::Vector2f{ snakePartSize, snakePartSize });
	}

	return dynamic_cast<Snake*>(gameObjectStore.addGameObject(std::move(snake)));
}

Consumable* GameObjectFactory::createFood01(sf::Vector2f position)
{
	float size{ 20.f };
	auto food01 = std::make_unique<Consumable>(1);

	auto transform = food01->addComponent<Transform>();
	transform->setPosition(position);

	food01->addComponent<BoxCollider>(transform, position, sf::Vector2f{ size, size });

	sf::Sprite sprite{};
	sprite.setOrigin({ size / 2.f, size / 2.f });
	sprite.setTexture(textureStore.getFood01Texture());
	sprite.setPosition(position);
	food01->addComponent<MeshRenderer>(sprite);

	return dynamic_cast<Consumable*>(gameObjectStore.addGameObject(std::move(food01)));
}
