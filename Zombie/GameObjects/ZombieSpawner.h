#pragma once
#include "GameObject.h"
#include "ZombieGo.h"

class SceneGame;
class TileMap;

class ZombieSpawner : public GameObject
{
protected:
	// Ÿ�� �������� �̾Ƽ� ���� Ÿ������ �迭
	std::vector<ZombieGo::Types> zombieTypes; 
	TileMap* tileMap = nullptr;
	SceneGame* sceneGame = nullptr;
	float interval = 1.f; // ���� ���� �ֱ�
	// float intervalMin;
	// float intervalMax;

	int spawnCount = 1; // �ѹ��� ���� ���� ����
	// int spawnCountMin; 
	// int spawnCountMax; 

	float radius = 250.f; // ���� �ݰ�

	float timer = 0.f;

public:
	ZombieSpawner(const std::string& name = "");
	~ZombieSpawner() override = default;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
};

