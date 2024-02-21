#pragma once
#include "SpriteGo.h"
class Player;
class Scene;

class ZombieGo : public SpriteGo
{
public:
	enum class Types // 좀비의 타입
	{
		Bloater,
		Chase,
		Crawler,
	};
	static const int TotalTypes = 3;
	static ZombieGo* Create(Types zombieType);

public:
	ZombieGo(const std::string& name = "");
	~ZombieGo() override = default;
	// 플레이어 방향 
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