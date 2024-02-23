#pragma once
#include "SpriteGo.h"
class Player;
class Scene;
class TileMap;
class SceneGame;

class ZombieGo : public SpriteGo
{
public:
	enum class Types // ������ Ÿ��
	{
		Bloater,
		Chase,
		Crawler,
	};
	static const int TotalTypes = 3;
	static ZombieGo* Create(Types zombieType);
	sf::Vector2f direction;
	TileMap* tileMap = nullptr;
	SceneGame* sceneGame = nullptr;

public:
	ZombieGo(const std::string& name = "");
	~ZombieGo() override = default;
	// �÷��̾� ���� 
	// Magnitude (player position - zombie position)

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void ZombieDied();


protected:
	Types type;
	int maxHp;
	float speed;
	int hp;
	Player* player;

};