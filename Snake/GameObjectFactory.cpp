#include "GameObjectFactory.h"
#include "BoxCollider.h"

GameObjectFactory::GameObjectFactory(TextureStore textureStore, GameObjectStore& gameObjectStore)
	:
	textureStore{ textureStore },
	gameObjectStore{ gameObjectStore }
{
}

shared_ptr<Snake> GameObjectFactory::createSnake()
{
	auto snake = std::make_shared<Snake>();

	auto transform{ make_shared<Transform>() };
	transform->setForward({ 1.f, 0.f });
	transform->setPosition({500.f, 150.f});
	snake->addComponent(transform);
	snake->addComponent(make_shared<SnakeMovement>(1.f));
	snake->getComponent<SnakeMovement>()->addComponent(transform);
	sf::Vector2f snakePartSize{ 20, 20 };
	int snakePartCount{ 5 };
	sf::Vector2f position{ snakePartCount * snakePartSize.x, snakePartSize.y };
	sf::Sprite sprite{};
	sprite.setOrigin(snakePartSize / 2.f);
	sprite.setTexture(textureStore.getTestTexture());

	for (size_t i = 0; i < snakePartCount; i++)
	{
		auto meshRenderer{ make_shared<MeshRenderer>(sprite) };
		auto boxCollider{ make_shared<BoxCollider>(transform.get(), snakePartSize)};
		snake->addComponent(meshRenderer);
		snake->addComponent(boxCollider);
	}


	snake->getComponent<SnakeMovement>()->awake();
	snake->awake();

	gameObjectStore.addGameObject(snake);
	return snake;
}