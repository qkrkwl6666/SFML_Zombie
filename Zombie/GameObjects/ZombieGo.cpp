#include "pch.h"
#include "ZombieGo.h"
#include "Player.h"
#include "Scene.h"
#include "TileMap.h"
#include "SceneGame.h"

// 플레이어에 접근한 좀비 삭제

ZombieGo* ZombieGo::Create(Types zombieType)
{
	ZombieGo* zombie = new ZombieGo("Zombie");
	zombie->type = zombieType;

	switch (zombieType)
	{
		case Types::Bloater:
			zombie->textureId = "graphics/bloater.png";
			zombie->maxHp = 40;
			zombie->speed = 100;
			zombie->attack = 20;
			zombie->attackInterval = 1.f;
			break;
		case Types::Chase:
			zombie->textureId = "graphics/chaser.png";
			zombie->maxHp = 70;
			zombie->speed = 75;
			zombie->attack = 40;
			zombie->attackInterval = 0.5f;
			break;
		case Types::Crawler:
			zombie->textureId = "graphics/crawler.png";
			zombie->maxHp = 20;
			zombie->speed = 50;
			zombie->attack = 50;
			zombie->attackInterval = 0.25f;
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

	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
	hp = maxHp;
	attackTimer = attackInterval;
}

void ZombieGo::Release()
{
	SpriteGo::Release();
}

void ZombieGo::Reset()
{
	SpriteGo::Reset();

	hp = maxHp;
	isAlive = true;
	player = dynamic_cast<Player*>(SCENE_MGR.GetCurrentScene()
		->FindGo("Player"));

	sceneGame = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
}

void ZombieGo::Update(float dt)
{
	SpriteGo::Update(dt);

	if (!isAlive)
	{
		return;
	}

	if (player == nullptr)
	{
		return;
	}

	direction = player->GetPosition() - position;

	Utils::Nomalize(direction);

	sf::Vector2f pos = position + direction * speed * dt;

	if (sceneGame)
	{
		pos = sceneGame->ClampByTileMap(pos);
	}

	SetPosition(pos);


	//if (tileMap != nullptr)
	//{
	//	sf::FloatRect tileMapBounds = tileMap->GetGlobalBounds();
	//	sf::Vector2f cellSize = tileMap->GetCellSize();

	//	tileMapBounds.left += cellSize.x;
	//	tileMapBounds.top += cellSize.y;

	//	tileMapBounds.width -= cellSize.x * 2.f;
	//	tileMapBounds.height -= cellSize.y * 2.f;

	//	pos.x = Utils::Clamp(pos.x, tileMapBounds.left,
	//		tileMapBounds.left + tileMapBounds.width);

	//	pos.y = Utils::Clamp(pos.y, tileMapBounds.top,
	//		tileMapBounds.top + tileMapBounds.height);
	//}

	//Translate(direction * speed * dt);

	SetRotation(Utils::Angle(direction));

	//충돌처리
	// Utils::Distance 거리 반환
	
	//if (Utils::Distance(position, player->GetPosition()) < 50.f) 
	//{
	//	SCENE_MGR.GetCurrentScene()->RemoveGo(this);
	//}

	//ZombieDied();

	//좀비가 플레이어 위치 근처에 갔으면
	// 거리를 재서 세팅한값보다 낮아지면 방향 off



}

void ZombieGo::FixedUpdate(float dt)
{
	attackTimer += dt;

	if (attackTimer > attackInterval)
	{
		if (GetGlobalBounds().intersects(player->GetGlobalBounds()))
		{
			player->OnDamage(attack);
			attackTimer = 0.f;
		}
	}


}

void ZombieGo::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void ZombieGo::ZombieDied()
{
	sf::FloatRect playerBounds = player->GetGlobalBounds();
	sf::FloatRect zombieBounds = sprite.getGlobalBounds();

	if (playerBounds.intersects(zombieBounds))
	{
		isRemove = true;
		//SCENE_MGR.GetCurrentScene()->RemoveGo((GameObject*)(this));
	}
}

int ZombieGo::GetAttack()
{
	return attack;
}

void ZombieGo::OnDamage(int damage)
{
	if (!isAlive)
		return;

	hp -= damage;
	if (hp <= 0)
	{
		hp = 0;
		OnDie();
	}
}

void ZombieGo::OnDie()
{
	if (!isAlive)
		return;

	isAlive = false;
	SetActive(false);
	sceneGame->RemoveGo(this);
}
