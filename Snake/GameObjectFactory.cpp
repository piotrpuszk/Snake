#include "GameObjectFactory.h"
#include "BoxCollider.h"

GameObjectFactory::GameObjectFactory(TextureStore textureStore, GameObjectStore& gameObjectStore)
	:
	textureStore{ textureStore },
	gameObjectStore{ gameObjectStore }
{
}

std::shared_ptr<Snake> GameObjectFactory::createSnake()
{
	float snakePartSize{ 20.f };
	size_t snakePartCount{ 5 };
	std::shared_ptr<TurnPointStore> turnPointStore{std::make_shared<TurnPointStore>()};
	SnakeComponentPositionIterator snakeComponentPositionIterator{ turnPointStore, snakePartCount, snakePartSize };
	auto snake = std::make_shared<Snake>(turnPointStore, snakeComponentPositionIterator);

	auto transform{ std::make_shared<Transform>() };
	transform->setForward({ 1.f, 0.f });
	transform->setPosition({ 500.f, 150.f });
	snake->addComponent(transform);
	snake->addComponent(std::make_shared<SnakeMovement>(1.f));
	snake->getComponent<SnakeMovement>()->addComponent(transform);
	sf::Vector2f position{ snakePartCount * snakePartSize, snakePartSize };
	sf::Sprite sprite{};
	sprite.setOrigin({ snakePartSize / 2.f, snakePartSize / 2.f });
	sprite.setTexture(textureStore.getTestTexture());

	for (size_t i = 0; i < snakePartCount; i++)
	{
		auto meshRenderer{ std::make_shared<MeshRenderer>(sprite) };
		auto boxCollider{ std::make_shared<BoxCollider>(transform.get(), sf::Vector2f{}, sf::Vector2f{snakePartSize, snakePartSize}) };
		snake->addComponent(meshRenderer);
		snake->addComponent(boxCollider);
	}


	snake->getComponent<SnakeMovement>()->awake();
	snake->awake();

	gameObjectStore.addGameObject(snake);
	return snake;
}