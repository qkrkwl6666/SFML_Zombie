#include "pch.h"
#include "Bullet.h"
#include "SceneGame.h"
#include "ZombieGo.h"

Bullet::Bullet(const std::string& name) : SpriteGo(name)
{
}

void Bullet::Fire(const sf::Vector2f& dir, float s , int d)
{
	direction = dir;
	speed = s;
	damage = d;
	SetRotation(Utils::Angle(direction));
}

void Bullet::Init()
{
	SpriteGo::Init();
	SetTexture("graphics/bullet.png");
	SetOrigin(Origins::ML);
	SetScale({4.f , 4.f });
}

void Bullet::Reset()
{
	SpriteGo::Reset();

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
	
}

void Bullet::Update(float dt)
{
	SpriteGo::Update(dt);

	SetPosition(position + direction * speed * dt);

	if (sceneGame)
	{
		if (!sceneGame->IsInTileMap(position))
		{
			SetActive(false);
			sceneGame->RemoveGo(this);
		}
	}
}

void Bullet::FixedUpdate(float dt)
{
	auto& list = sceneGame->GetZombieList();

	for (auto zombie : list)
	{
		if (!zombie->GetActive())
		{
			continue;
		}

		if (GetGlobalBounds().intersects(zombie->GetGlobalBounds()))
		{
			SetActive(false);
			sceneGame->RemoveGo(this);

			ZombieGo* zombieGo = dynamic_cast<ZombieGo*>(zombie);
			if (zombieGo)
			{
				zombieGo->OnDamage(damage); 
			}
			break;
		}
	}
}
