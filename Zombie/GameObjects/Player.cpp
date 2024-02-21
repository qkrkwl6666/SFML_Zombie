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

void Player::Update(float dt)
{
	InputMgr::Clear();
	SpriteGo::Update(dt);

	sf::Vector2f mousePos = InputMgr::GetMousePos();
	sf::Vector2f mouseWorldPos = mousePos;

	//ObjectPos = sprite.getPosition();
	//if (InputMgr::GetMouseButtonUp(sf::Mouse::Button::Left))
	//{
	//	currentMousePos.x = sf::Mouse::getPosition().x;
	//	currentMousePos.y = sf::Mouse::getPosition().y;
	//	currentPlayerPos = sprite.getPosition();
	//}
	//direction = currentMousePos - currentPlayerPos;
	//float length = Utils::Magnitude(direction);
	//ObjectPos += direction * speed * dt;
	//sprite.setPosition(ObjectPos);

	float h = InputMgr::GetAxis(Axis::Horizontal);
	float v = InputMgr::GetAxis(Axis::Vertical);

	direction.x = h;
	direction.y = v;

	if (Utils::Magnitude(direction) > 1.f)
	{
		Utils::Nomalize(direction);
	}

	//Translate(position + direction * speed * dt);

	SetPosition(position + direction * speed * dt);

	//sf::Vector2f pos = sprite.getPosition();
	//pos.x += h * speed * dt;
	//pos.y += v * speed * dt;

	//sprite.setPosition(pos);

	look = mouseWorldPos - position;
	Utils::Nomalize(look);
	SetRotation(Utils::Angle(look));

}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
