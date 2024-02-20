#include "pch.h"
#include "SceneGame.h"
#include "Player.h"

SceneGame::SceneGame(SceneIds id) : Scene(id)
{
	
}

void SceneGame::Init()
{
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

	player->SetPosition({500.f , 500.f});
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
}
