#include "pch.h"
#include "TileMap.h"

TileMap::TileMap(const std::string& name) : GameObject(name)
{
}

void TileMap::Set(const sf::Vector2i& count,const sf::Vector2f& size)
{
	cellCount = count;
	cellSize = size;

	va.clear();
	va.setPrimitiveType(sf::Quads);
	va.resize(count.x * count.y * 4); // 실제 배열 크기 할당
	this->size = count.x * count.y * 4;
	sf::Vector2f posOffset[4] =
	{
		{ 0, 0 },
		{ size.x, 0 },
		{ size.x, size.y },
		{ 0, size.y },
	};

	sf::Vector2f texCoord0[4] =
	{
		{ 0, 0 },
		{ 50.f, 0 },
		{ 50.f, 50.f },
		{ 0, 50.f },
	};

	for (int i = 0; i < count.y; i++)
	{
		for (int j = 0; j < count.x; j++)
		{
			int texIndex = Utils::RandomRange(0, 3);

			if (i == 0 || i == count.y - 1 || j == 0 || j == count.x - 1)
			{
				texIndex = 3; // 벽 텍스처
			}

			int quadindex = i * count.x + j; // 1차원
			sf::Vector2f quadPos(size.x * j, size.y * i);

			for (int k = 0; k < 4; k++)
			{
				int vertexIndex = (quadindex * 4) + k;
				va[vertexIndex].position = quadPos + posOffset[k];
				va[vertexIndex].texCoords = texCoord0[k];
				va[vertexIndex].texCoords.y += texIndex * 50.f;
			}
		}
	}
	bounds = va.getBounds();
}


void TileMap::SetOrigin(Origins preset)
{
	if (preset == Origins::Custom)
		return;

	originPreset = preset;
	sf::FloatRect bounds = va.getBounds();
	origin.x = bounds.width * ((int)originPreset % 3) * 0.5f;
	origin.y = bounds.height * ((int)originPreset / 3) * 0.5f;
	UpdateTransform();
}

void TileMap::SetOrigin(const sf::Vector2f& newOrigin) 
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	UpdateTransform();
}



void TileMap::SetSpriteSheetId(const std::string& id)
{
	spriteSheetId = id;
	texture = &RES_MGR_TEXTURE.Get(spriteSheetId);
}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}

void TileMap::Translate(const sf::Vector2f& delta)
{
	GameObject::Translate(delta);
	UpdateTransform();
}

void TileMap::UpdateTransform()
{
	// S R T
	transform = sf::Transform::Identity;

	float scaleX = isFlipX ? -scale.x : scale.x;
	float scaleY = isFlipY ? -scale.y : scale.y;

	transform.scale(scaleX , scaleX , position.x, position.y);
	transform.rotate(rotation, position.x, position.y);
	transform.translate(position - origin);

}

sf::FloatRect TileMap::GetLocalBounds()
{
	sf::FloatRect bounds = va.getBounds();

	// 오리진 좌표 갱신
	bounds.left = origin.x;
	bounds.top = origin.y;

	return bounds;
}

sf::FloatRect TileMap::GetGlobalBounds()
{
	sf::FloatRect bounds = va.getBounds();

	return transform.transformRect(bounds);
}

const sf::Vector2i& TileMap::GetCellCount() const
{
	return cellCount;
}

const sf::Vector2f& TileMap::GetCellSize() const
{
	return cellSize;
}

void TileMap::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	UpdateTransform();
}

void TileMap::SetFlipX(bool flip)
{
	GameObject::SetFlipX(flip);
	UpdateTransform();
}

void TileMap::SetFlipY(bool flip)
{
	GameObject::SetFlipY(flip);
	UpdateTransform();
}

void TileMap::SetRotation(float r)
{
	GameObject::SetRotation(r);
	UpdateTransform();
}

void TileMap::Init()
{
	GameObject::Init();
	SetSpriteSheetId("graphics/background_sheet.png");
	Set({ 10,10 }, { 50.f, 50.f });
	//SetOrigin(Origins::MC);
}

void TileMap::Release()
{
	GameObject::Release();
}

void TileMap::Reset()
{
	GameObject::Reset();

}

void TileMap::Update(float dt)
{
	GameObject::Update(dt);

}

void TileMap::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;

	window.draw(va, state);
}
