#include "pch.h"
#include "Player.h"

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

	SetPosition(position + direction * speed * dt);

	look = mouseWorldPos - position;
	Utils::Nomalize(look);
	SetRotation(Utils::Angle(look));

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
