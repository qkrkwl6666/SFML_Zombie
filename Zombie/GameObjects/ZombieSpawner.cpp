#include "pch.h"
#include "ZombieSpawner.h"
#include "TileMap.h"

ZombieSpawner::ZombieSpawner(const std::string& name)
	: GameObject(name)
{

}

void ZombieSpawner::Init()
{
	GameObject::Init();
}

void ZombieSpawner::Release()
{
	GameObject::Release();
}

void ZombieSpawner::Reset()
{
	GameObject::Reset();
	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));

	zombieTypes.clear();
	zombieTypes.push_back(ZombieGo::Types::Bloater);
	zombieTypes.push_back(ZombieGo::Types::Chase);
	zombieTypes.push_back(ZombieGo::Types::Chase);
	zombieTypes.push_back(ZombieGo::Types::Chase);
	zombieTypes.push_back(ZombieGo::Types::Crawler);
	zombieTypes.push_back(ZombieGo::Types::Crawler);

	interval = 1.f;
	spawnCount = 1;
	radius = 250.f;
	timer = 0.f;

}

void ZombieSpawner::Update(float dt)
{
	GameObject::Update(dt);

	timer += dt;

	if (timer > interval) 
	{
		timer = 0.f;

		for (int i = 0; i < spawnCount; i++) 
		{
			//sf::Vector2f pos = position +
			//	Utils::RandomInUnitCircle() * radius;
			sf::FloatRect tileMapBounds = tileMap->GetGlobalBounds();
			int randomPos = Utils::RandomRange(0, 4);
			sf::Vector2f cellSize = tileMap->GetCellSize();

			tileMapBounds.left += cellSize.x;
			tileMapBounds.top += cellSize.y;

			tileMapBounds.width -= cellSize.x * 2.f;
			tileMapBounds.height -= cellSize.y * 2.f;

			sf::Vector2f pos = tileMapBounds.getPosition();

			switch (randomPos)
			{
				case 0:
					break;
				case 1:
					pos += {tileMapBounds.width, 0.f};
					break;
				case 2:
					pos += {0.f , tileMapBounds.height};
					break;
				case 3:
					pos += {tileMapBounds.width , tileMapBounds.height};
					break;
			}

			ZombieGo::Types zombieType = zombieTypes
				[Utils::RandomRange(0, zombieTypes.size())];

			ZombieGo* zombie = ZombieGo::Create(zombieType);
			zombie->Init();
			zombie->Reset();
			zombie->SetPosition(pos); 

			SCENE_MGR.GetCurrentScene()->AddGo(zombie);

		}
	}
}
