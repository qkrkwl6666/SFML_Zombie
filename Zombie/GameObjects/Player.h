#pragma once
#include "SpriteGo.h"

class SceneGame;
class TileMap;
class Player : public SpriteGo
{
protected:
	sf::Vector2f direction = { 0.f , 0.f }; // 방향
	sf::Vector2f look = {1.0f , 0.f}; // 회전
	float speed = 700.f;
	sf::Vector2f currentMousePos = { 0.f , 0.f };
	sf::Vector2f currentPlayerPos = { 0.f , 0.f };
	sf::Vector2f ObjectPos = { 0.f , 0.f };

	std::string textureId;

	bool isFiring = false;
	float fireInterval = 0.5f;
	float fireTimer = 0.f;
	float bulletSpeed = 1000.f;
	int bulletDagame = 10;
	SceneGame* sceneGame = nullptr;

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

	 void Fire();

};

