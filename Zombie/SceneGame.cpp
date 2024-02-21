#include "pch.h"
#include "SceneGame.h"
#include "Player.h"
#include "TileMap.h"

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

	sf::Vector2f centerPos = (sf::Vector2f)FRAMEWORK.GetWindowSize() * 0.5f;

	TileMap* tileMap = dynamic_cast<TileMap*>(FindGo("Background"));
	tileMap->SetPosition(centerPos);
	tileMap->SetOrigin(Origins::MC);
	player->SetPosition(centerPos);

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
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.draw(triangle);
}
