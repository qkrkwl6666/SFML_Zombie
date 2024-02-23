#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"
#include "ZombieGo.h"
#include "ZombieSpawner.h"
#include "TextGo.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
	
}

void SceneGame::Init()
{

	//AddGo(new TileMap("Background"));

	spawners.push_back(new ZombieSpawner());
	spawners.push_back(new ZombieSpawner());

	for (auto data : spawners) 
	{
		data->SetPosition(Utils::RandomOnUnitCircle() * 250.f);
		AddGo(data);
	}

	player = new Player("Player");
	AddGo(player);

	tileMap = new TileMap("Background");
	tileMap->sortLayer = -1;

	AddGo(tileMap);

	// UI SCORE

	gameOver = new TextGo("GameOver");
	gameOver->SetOrigin(Origins::MC);
	gameOver->SetCharacterSize(100);
	gameOver->SetString("GameOver!");
	gameOver->SetFont("fonts/zombiecontrol.ttf");
	gameOver->SetPosition({ 0 , 0 });
	//gameOver->sortLayer = 10;
	AddGo(gameOver, Layers::Ui);
	gameOver->SetActive(false);

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
	FindGoAll("Zombie", zombieList, Layers::World);

	Scene::Update(dt);
	
	if (!playerRemove)
	{
		worldView.setCenter(player->GetPosition());
	}
	if (playerRemove)
	{
		tileMap->sortLayer = 10;
		ResortGo(tileMap);
	}


	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	ZombieGo::Types zombieType =
	//		(ZombieGo::Types)Utils::RandomRange(0, ZombieGo::TotalTypes);

	//	ZombieGo* zombie = ZombieGo::Create(zombieType);

	//	zombie->Init();

	//	zombie->Reset();

	//	zombie->SetPosition(Utils::RandomInUnitCircle() * 500.f);

	//	AddGo(zombie);
	//}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
		if (tileMap->sortLayer == -1)
		{
			tileMap->sortLayer = 1;
		}
		else
		{
			tileMap->sortLayer = -1;
		}
		ResortGo(tileMap);
	}
}

void SceneGame::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneGame::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	
}

void SceneGame::SetGameOverActive(bool a)
{
	gameOver->SetActive(a);
}

sf::Vector2f SceneGame::ClampByTileMap(const sf::Vector2f& point)
{

	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect , tileMap->GetCellSize() * -2.f);
	return Utils::Clamp(point , rect);

}

bool SceneGame::IsInTileMap(const sf::Vector2f& point)
{
	sf::FloatRect rect = tileMap->GetGlobalBounds();
	rect = Utils::ResizeRect(rect, tileMap->GetCellSize() * -2.f);

	return rect.contains(point);
}
