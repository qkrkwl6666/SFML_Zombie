#pragma once
#include "GameObject.h"
#include "ZombieGo.h"

class SceneGame;
class TileMap;

class ZombieSpawner : public GameObject
{
protected:
	// 타입 랜덤별로 뽑아서 생성 타입저장 배열
	std::vector<ZombieGo::Types> zombieTypes; 
	TileMap* tileMap = nullptr;
	SceneGame* sceneGame = nullptr;
	float interval = 1.f; // 좀비 스폰 주기
	// float intervalMin;
	// float intervalMax;

	int spawnCount = 1; // 한번에 좀비 스폰 개수
	// int spawnCountMin; 
	// int spawnCountMax; 

	float radius = 250.f; // 스폰 반경

	float timer = 0.f;

public:
	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
};

