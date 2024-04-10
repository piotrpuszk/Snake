#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory(TextureStore textureStore, GameObjectStore& gameObjectStore)
	:
	textureStore{ textureStore },
	gameObjectStore{ gameObjectStore }
{
}

shared_ptr<Snake> GameObjectFactory::createSnake()
{
	vector<shared_ptr<SnakePart>> snakeParts{};
	sf::Vector2f snakePartSize{ 20, 20 };
	int snakePartCount{ 20 };
	sf::Vector2f position{ snakePartCount * snakePartSize.x, snakePartSize.y };
	for (size_t i = 0; i < snakePartCount; i++)
	{
		auto snakePart{ createSnakePart(snakePartSize) };
		snakePart.get()->getComponent<Transform>()->setPosition(position);
		position -= {snakePartSize.x, 0.f};
		if (i == 0)
		{
			snakePart.get()->markAsHead();
		}
		if (i == snakePartCount - 1)
		{
			snakePart.get()->markAsTail();
		}
		snakeParts.push_back(snakePart);
	}
	Snake snake{ snakeParts };
	auto snakePtr = std::make_shared<Snake>(snake);
	snakePtr.get()->awake();
	gameObjectStore.addGameObject(snakePtr);
	return snakePtr;
}

shared_ptr<SnakePart> GameObjectFactory::createSnakePart(sf::Vector2f snakePartSize)
{
	SnakePart snakePart{};
	shared_ptr<Transform> transform = std::make_shared<Transform>();
	shared_ptr<SnakeMovement> snakeMovement = std::make_shared<SnakeMovement>(5.f);
	shared_ptr<BoxCollider> boxCollider = std::make_shared<BoxCollider>(*transform, snakePartSize);

	sf::Sprite sprite{};
	sprite.setOrigin(snakePartSize / 2.f);
	sprite.setTexture(textureStore.getTestTexture());
	shared_ptr<MeshRenderer> meshRenderer = std::make_shared<MeshRenderer>(sprite);
	snakePart.addComponent(transform);
	snakePart.addComponent(snakeMovement);
	snakePart.addComponent(boxCollider);
	snakePart.addComponent(meshRenderer);
	snakeMovement->addComponent(transform);

	transform->setForward({ 1.f, 0.f });

	snakeMovement->awake();
	snakePart.awake();

	auto snakePartPtr{ std::make_shared<SnakePart>(snakePart) };
	gameObjectStore.addGameObject(snakePartPtr);

	return snakePartPtr;
}
