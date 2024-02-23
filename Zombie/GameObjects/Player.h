#pragma once
#include "SpriteGo.h"

class SceneGame;
class TileMap;
class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f , 0.f }; // ����
	sf::Vector2f look = {1.0f , 0.f}; // ȸ��
	float speed = 700.f;
	sf::Vector2f currentMousePos = { 0.f , 0.f };
	sf::Vector2f currentPlayerPos = { 0.f , 0.f };
	sf::Vector2f ObjectPos = { 0.f , 0.f };

	std::string textureId;

	bool isFiring = false;
	float fireInterval = 0.5f;
	float fireTimer = 0.f;
	float bulletSpeed = 1000.f;
	int bulletDagame = 30;
	float time = 0.f;
	float timeScale = 1.f;
	float damageTime = 3.f;
	SceneGame* sceneGame = nullptr;

	bool isAlive = true;
	bool isNoDamage = false;
	float noDamageTime = 5.f;
	float isDamageTimer = 0.f;

	int maxHp = 100;
	int currentHp = 100;


public:
	Player(const std::string& name = "");
	~Player() override = default;

	 void Init() override;
	 void Release() override;
	 void Translate(const sf::Vector2f& delta);
	 void Reset() override;

	 sf::FloatRect GetGlobalBounds();
	 void Update(float dt) override;

	 void FixedUpdate(float dt) override;
	 void Draw(sf::RenderWindow& window) override;

	 void OnDamage(int damage);
	 bool isDead();

	 void InDamagePlayer(int damage);
	 void OnDie();

	 void Fire();

};

