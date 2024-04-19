#include "GameObjectFactory.h"
#include <iostream>

GameObjectFactory::GameObjectFactory(TextureStore textureStore, GameObjectStore& gameObjectStore)
	:
	textureStore{ textureStore },
	gameObjectStore{ gameObjectStore }
{
}

Snake* GameObjectFactory::createSnake()
{
	float snakePartSize{ 20.f };
	size_t snakePartCount{ 10 };

	auto snake = std::make_unique<Snake>();

	const auto& turnPointStore{ snake->addComponent<TurnPointStore>() };
	snake->addComponent<GeneratorOfSnakePartPositions>(turnPointStore, snakePartCount, snakePartSize);
	auto transform{ snake->addComponent<Transform>() };
	transform->setForward({ 1.f, 0.f });
	transform->setPosition({ 300.f, 150.f });
	snake->addComponent<SnakeCollisionChecker>(transform, snakePartSize);
	snake->addComponent<SnakeMovement>(transform, 5.f, snakePartSize);

	sf::Sprite sprite{};
	sprite.setOrigin({ snakePartSize / 2.f, snakePartSize / 2.f });
	sprite.setTexture(textureStore.getTest());
	sprite.setTextureRect(sf::IntRect{ 0, 0, 20, 20 });
	for (size_t i = 0; i < snakePartCount; i++)
	{
		snake->addComponent<MeshRenderer>(sprite);
	}
	snake->addComponent<BoxCollider>(transform, transform->getPosition(), sf::Vector2f{snakePartSize, snakePartSize});

	return dynamic_cast<Snake*>(gameObjectStore.addGameObject(std::move(snake)));
}

Consumable* GameObjectFactory::createConsumable(sf::Vector2f position, size_t growSize)
{
	float size{ 20.f };
	auto food01 = std::make_unique<Consumable>(growSize);

	auto transform = food01->addComponent<Transform>();
	transform->setPosition(position);

	food01->addComponent<BoxCollider>(transform, position, sf::Vector2f{ size, size });

	sf::Sprite sprite{};
	sprite.setOrigin({ size / 2.f, size / 2.f });
	sprite.setTexture(textureStore.getFood01());
	sprite.setPosition(position);
	food01->addComponent<MeshRenderer>(sprite);

	return dynamic_cast<Consumable*>(gameObjectStore.addGameObject(std::move(food01)));
}

ConsumablesSpawner* GameObjectFactory::createConsumablesSpawner(const sf::Vector2f& position, const sf::Vector2f& size, sf::Time spawnInterval)
{
	auto consumablesSpawner{ std::make_unique<ConsumablesSpawner>(position, size, spawnInterval)};

	return dynamic_cast<ConsumablesSpawner*>(gameObjectStore.addGameObject(std::move(consumablesSpawner)));
}

Wall* GameObjectFactory::createWall(sf::Vector2f meshRendererPosition, sf::Vector2f meshRendererSize, sf::Vector2f boxColliderPosition, sf::Vector2f boxColliderSize)
{
	auto wall{ std::make_unique<Wall>() };

	auto transform{ wall->addComponent<Transform>() };
	wall->addComponent<BoxCollider>(transform, boxColliderPosition, boxColliderSize);

	sf::Sprite sprite{};
	const auto& texture{ textureStore.getBrick01() };
	sprite.setTexture(texture);
	sf::Vector2f scale{ meshRendererSize.x / texture.getSize().x, meshRendererSize.y / texture.getSize().y };
	sprite.setScale(scale);
	sprite.setPosition(meshRendererPosition);
	wall->addComponent<MeshRenderer>(sprite);

	return dynamic_cast<Wall*>(gameObjectStore.addGameObject(std::move(wall)));
}

BackgroundTexture* GameObjectFactory::createBackgroundTexture(sf::Vector2f position, sf::Vector2f size)
{
	auto backgroundTexture{ std::make_unique<BackgroundTexture>() };
	sf::Sprite sprite{};
	const auto& texture{ textureStore.getBackground() };
	sprite.setTexture(texture);
	sf::Vector2f scale{ size.x / texture.getSize().x, size.y / texture.getSize().y };
	sprite.setScale(scale);
	sprite.setPosition(position);
	backgroundTexture->addComponent<MeshRenderer>(sprite, -1);

	return dynamic_cast<BackgroundTexture*>(gameObjectStore.addGameObject(std::move(backgroundTexture)));
}