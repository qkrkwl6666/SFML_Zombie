#pragma once
#include "Scene.h"

class TextGo;
class ZombieSpawner;
class Player;
class TileMap;
class ZombieGo;
class GameObject;

class SceneGame : public Scene
{
protected:
	Player* player = nullptr;
	std::vector<ZombieSpawner*> spawners;
	std::list<GameObject*> zombieList;

	TileMap* tileMap = nullptr;

	sf::VertexArray triangle;
	TextGo* score;
	TextGo* gameOver;


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

	void SetGameOverActive(bool a);

	const std::list<GameObject*>& GetZombieList() 
		const { return zombieList; }

	bool playerRemove = false;

	sf::Vector2f ClampByTileMap(const sf::Vector2f& point);
	bool IsInTileMap(const sf::Vector2f& point);
};

