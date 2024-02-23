#pragma once
#include "Scene.h"

class ZombieSpawner;
class Player;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	std::vector<ZombieSpawner*> spawners;

	sf::VertexArray triangle;

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

