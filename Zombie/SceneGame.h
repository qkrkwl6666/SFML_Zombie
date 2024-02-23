#pragma once
#include "Scene.h"

class TextGo;
class ZombieSpawner;
class Player;
class TileMap;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	std::vector<ZombieSpawner*> spawners;
	TileMap* tileMap = nullptr;

	sf::VertexArray triangle;
	TextGo* score;
	

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void LateUpdate(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);
	bool IsInTileMap(const sf::Vector2f& point);
};

