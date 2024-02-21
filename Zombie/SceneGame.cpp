#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "ZombieGo.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
	
}

void SceneGame::Init()
{
	AddGo(new TileMap("Background"));

	player = new Player("Player");
	
	AddGo(player);

	Scene::Init();
}

void SceneGame::Release()
{
	Scene::Release();
}

void SceneGame::Enter()
{
	Scene::Enter();

	sf::Vector2f windowSize = (sf::Vector2f)FRAMEWORK.GetWindowSize();
	sf::Vector2f centerPos = windowSize * 0.f;

	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f, 0.f });
	uiView.setSize(windowSize);
	uiView.setCenter(centerPos);
	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));

	tileMap->SetPosition({ 0.f, 0.f });
	tileMap->SetOrigin(Origins::MC);
	player->SetPosition({ 0.f, 0.f });

	//tileMap->SetRotation(45);
	//tileMap->SetScale({ 2.5f , 2.5f });

}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);

	worldView.setCenter(player->GetPosition());

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		ZombieGo::Types zombieType =
			(ZombieGo::Types)Utils::RandomRange(0, ZombieGo::TotalTypes);

		ZombieGo* zombie = ZombieGo::Create(zombieType);

		zombie->Init();

		zombie->Reset();

		zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);

		AddGo(zombie);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	
}
