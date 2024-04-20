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
	snake->addComponent(std::make_unique<TextureStore>(textureStore));
	snake->addComponent<TurnPointTextureSelector>(std::make_unique<TextureStore>(textureStore));
	transform->setForward({ 1.f, 0.f });
	transform->setPosition({ 300.f, 150.f });
	snake->addComponent<SnakeCollisionChecker>(transform, snakePartSize);
	snake->addComponent<SnakeMovement>(transform, 5.f, snakePartSize);

	sf::Sprite sprite{};
	sprite.setOrigin({ snakePartSize / 2.f, snakePartSize / 2.f });
	sprite.setTexture(textureStore.getSnakeHead());
	for (size_t i = 0; i < snakePartCount; i++)
	{
		if (i == snakePartCount - 1)
		{
			sprite.setTexture(textureStore.getSnakeTail());
		}
		snake->addComponent<MeshRenderer>(sprite);
		sprite.setTexture(textureStore.getSnakePart());
	}
	snake->addComponent<BoxCollider>(transform, transform->getPosition(), sf::Vector2f{ snakePartSize, snakePartSize });

	return dynamic_cast<Snake*>(gameObjectStore.addGameObject(std::move(snake)));
}

Consumable* GameObjectFactory::createConsumable(sf::Vector2f position, size_t growSize)
{
	auto food01 = std::make_unique<Consumable>(growSize);

	auto transform = food01->addComponent<Transform>();
	transform->setPosition(position);


	sf::Sprite sprite{};
	sprite.setTexture(textureStore.getFood01());
	const auto& size{ sprite.getTexture()->getSize() };
	sprite.setOrigin({ static_cast<float>(size.x) / 2.f, static_cast<float>(size.y) / 2.f });
	sprite.setPosition(position);
	food01->addComponent<MeshRenderer>(sprite);


	food01->addComponent<BoxCollider>(transform, position, sf::Vector2f{ static_cast<float>(size.x), static_cast<float>(size.y) });

	return dynamic_cast<Consumable*>(gameObjectStore.addGameObject(std::move(food01)));
}

ConsumablesSpawner* GameObjectFactory::createConsumablesSpawner(const sf::Vector2f& position, const sf::Vector2f& size, sf::Time spawnInterval)
{
	auto consumablesSpawner{ std::make_unique<ConsumablesSpawner>(position, size, spawnInterval) };

	return dynamic_cast<ConsumablesSpawner*>(gameObjectStore.addGameObject(std::move(consumablesSpawner)));
}

Wall* GameObjectFactory::createWall(sf::Vector2f meshRendererPosition,
	sf::Vector2f meshRendererGrowDirection,
	float meshRenderersCount,
	float meshRendererSize,
	sf::Vector2f boxColliderPosition,
	sf::Vector2f boxColliderSize)
{
	auto wall{ std::make_unique<Wall>() };

	auto transform{ wall->addComponent<Transform>() };
	wall->addComponent<BoxCollider>(transform, boxColliderPosition, boxColliderSize);
	sf::Vector2f position{ meshRendererPosition };

	for (size_t i{}; i < meshRendererSize; i++)
	{
		sf::Sprite sprite{};
		const auto& texture{ textureStore.getBrick01() };
		sprite.setTexture(texture);
		sf::Vector2f scale{ meshRendererSize / texture.getSize().x, meshRendererSize / texture.getSize().y };
		sprite.setScale(scale);
		sprite.setPosition(position);
		position += meshRendererGrowDirection * meshRendererSize;
		wall->addComponent<MeshRenderer>(sprite);
	}

	return dynamic_cast<Wall*>(gameObjectStore.addGameObject(std::move(wall)));
}

BackgroundTexture* GameObjectFactory::createBackgroundTexture(sf::Vector2f mapSize)
{
	auto backgroundTexture{ std::make_unique<BackgroundTexture>() };
	const auto& texture{ textureStore.getBackground() };
	sf::Vector2f position{};
	for (size_t row{}; row < mapSize.x / texture.getSize().x; row++)
	{
		for (size_t column{}; column < mapSize.x / texture.getSize().x; column++)
		{
			position = { row * static_cast<float>(texture.getSize().x), column * static_cast<float>(texture.getSize().y) };
			sf::Sprite sprite{};
			sprite.setTexture(texture);
			sprite.setPosition(position);
			backgroundTexture->addComponent<MeshRenderer>(sprite, -1000);
		}
	}

	return dynamic_cast<BackgroundTexture*>(gameObjectStore.addGameObject(std::move(backgroundTexture)));
}

GameOver* GameObjectFactory::createGameOver(sf::Vector2f position)
{
	auto gameOver{ std::make_unique<GameOver>() };
	const auto& texture{ textureStore.getGameOver() };
	sf::Sprite sprite{};
	sprite.setTexture(texture);
	sf::Vector2f textureHalfSize{ static_cast<float>(texture.getSize().x) * 0.5f, static_cast<float>(texture.getSize().y) * 0.5f };
	sprite.setPosition(position - textureHalfSize);
	gameOver->addComponent<MeshRenderer>(sprite, 1000);

	return dynamic_cast<GameOver*>(gameObjectStore.addGameObject(std::move(gameOver)));
}