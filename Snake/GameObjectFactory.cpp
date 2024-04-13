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
	size_t snakePartCount{ 15 };
	auto turnPointStore{std::make_unique<TurnPointStore>()};
	SnakeComponentPositionIterator snakeComponentPositionIterator{ turnPointStore.get(), snakePartCount, snakePartSize};
	auto snake = std::make_unique<Snake>(std::move(turnPointStore), snakeComponentPositionIterator);

	auto transform{ std::make_unique<Transform>() };
	transform->setForward({ 1.f, 0.f });
	transform->setPosition({ 500.f, 150.f });
	snake->addComponent(std::make_unique<SnakeMovement>(transform.get(), 1.f));
	sf::Vector2f position{ snakePartCount * snakePartSize, snakePartSize };
	sf::Sprite sprite{};
	sprite.setOrigin({ snakePartSize / 2.f, snakePartSize / 2.f });
	sprite.setTexture(textureStore.getTestTexture());

	for (size_t i = 0; i < snakePartCount; i++)
	{
		auto meshRenderer{ std::make_unique<MeshRenderer>(sprite) };
		auto boxCollider{ std::make_unique<BoxCollider>(transform.get(), sf::Vector2f{}, sf::Vector2f{snakePartSize, snakePartSize}) };
		snake->addComponent(std::move(meshRenderer));
		snake->addComponent(std::move(boxCollider));
	}

	snake->addComponent(std::move(transform));
	
	return dynamic_cast<Snake*>(gameObjectStore.addGameObject(std::move(snake)));
}