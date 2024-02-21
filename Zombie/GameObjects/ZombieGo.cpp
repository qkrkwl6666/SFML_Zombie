#include "pch.h"
#include "ZombieGo.h"
#include "Player.h"

ZombieGo* ZombieGo::Create(Types zombieType)
{
	ZombieGo* zombie = new ZombieGo();
	zombie->type = zombieType;

	switch (zombieType)
	{
		case Types::Bloater:
			zombie->textureId = "graphics/bloater.png";
			zombie->maxHp = 40;
			zombie->speed = 100;
			break;
		case Types::Chase:
			zombie->textureId = "graphics/chaser.png";
			zombie->maxHp = 70;
			zombie->speed = 75;
			break;
		case Types::Crawler:
			zombie->textureId = "graphics/crawler.png";
			zombie->maxHp = 20;
			zombie->speed = 50;
			break;
	}

	return zombie;
}

ZombieGo::ZombieGo(const std::string& name) : SpriteGo(name)
{

}

void ZombieGo::Init()
{
	SpriteGo::Init();
	SetTexture(textureId);
	SetOrigin(Origins::MC);
}

void ZombieGo::Release()
{
	SpriteGo::Release();
}

void ZombieGo::Reset()
{
	SpriteGo::Reset();

	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()
		->FindGo("Player"));
}

void ZombieGo::Update(float dt)
{
	SpriteGo::Update(dt);

	sf::Vector2f direction = player->GetPosition() - position;

	Utils::Nomalize(direction);

	sf::Vector2f pos = 
		(position = position + direction * dt * speed);
	
	SetPosition(pos);

	SetRotation(Utils::Angle(direction));

}

void ZombieGo::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
