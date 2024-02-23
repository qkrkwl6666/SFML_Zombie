#include "pch.h"
#include "Player.h"
#include "TileMap.h"

Player::Player(const std::string& name)
	: SpriteGo(name)
{

}

void Player::Init()
{
	SpriteGo::Init();
	InputMgr::Init();
	SetTexture("graphics/player.png");
	SetOrigin(Origins::MC);
}

void Player::Release()
{
	SpriteGo::Release();
}

void Player::Translate(const sf::Vector2f& delta)
{
	position += delta;
	sprite.setPosition(position);
}

void Player::Reset()
{
	SpriteGo::Reset();

	tileMap = dynamic_cast<TileMap*>(SCENE_MGR.GetCurrentScene()->FindGo("Background"));
}

sf::FloatRect Player::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}

void Player::Update(float dt)
{
	//InputMgr::Clear();
	SpriteGo::Update(dt);

	sf::Vector2i mousePos = (sf::Vector2i)InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = SCENE_MGR.GetCurrentScene()->ScreenToWorld(mousePos);

	float h = InputMgr::GetAxis(Axis::Horizontal);
	float v = InputMgr::GetAxis(Axis::Vertical);

	// View && Renderwindow ÇÊ¿äÇÔ 
	direction.x = h;
	direction.y = v;

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Nomalize(direction);
	}

	sf::Vector2f pos = position + direction * speed * dt;

	if (tileMap != nullptr)
	{
		sf::FloatRect tileMapBounds = tileMap->GetGlobalBounds();
		sf::Vector2f cellSize = tileMap->GetCellSize();

		tileMapBounds.left += cellSize.x;
		tileMapBounds.top += cellSize.y;

		tileMapBounds.width -= cellSize.x * 2.f;
		tileMapBounds.height -= cellSize.y * 2.f;

		pos.x = Utils::Clamp(pos.x , tileMapBounds.left , 
			tileMapBounds.left + tileMapBounds.width);

		pos.y = Utils::Clamp(pos.y, tileMapBounds.top,
			tileMapBounds.top + tileMapBounds.height);
	}

	SetPosition(pos);

	look = mouseWorldPos - position;
	Utils::Nomalize(look);
	SetRotation(Utils::Angle(look));

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
