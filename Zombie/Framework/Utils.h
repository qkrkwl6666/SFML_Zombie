#pragma once

class Utils
{
public:
	static float Clamp(float v, float min, float max);
	static sf::Vector2f Clamp(const sf::Vector2f& v, 
		const sf::FloatRect& rect);

	static sf::FloatRect ResizeRect(const sf::FloatRect& rect , 
		const sf::Vector2f& delta);

	// Random
	static float RandomValue(); // 0.0f ~ 1.0f
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnUnitCircle();
	static sf::Vector2f RandomInUnitCircle();
	static int RandomRange(int min, int maxExclude);

	// Origin
	static sf::Vector2f SetOrigin(sf::Transformable& obj, Origins originPreset, const sf::FloatRect& rect);
	static sf::Vector2f SetOrigin(sf::Sprite& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Text& obj, Origins originPreset);
	static sf::Vector2f SetOrigin(sf::Shape& obj, Origins originPreset);

	// Math
	static float SqrMagnitude(const sf::Vector2f& vec); //  ±Ê¿Ã * ±Ê¿Ã ¡¶∞ˆ
	static float Magnitude(const sf::Vector2f& vec); // ±Ê¿Ã
	static void Nomalize(sf::Vector2f& vec); // ∫§≈Õ¿« ±Ê¿Ã∏¶ 1∑Œ πŸ≤€ ∫§≈Õ ∫Ø»Ø 
	static sf::Vector2f GetNomalize(const sf::Vector2f& vec); // ∫§≈Õ¿« ±Ê¿Ã∏¶ 1∑Œ πŸ≤€ ∫§≈Õ ∫Ø»Ø 
	static float Distance(const sf::Vector2f& p1,
		const sf::Vector2f& p2);

	static float RadianToDegree(float radian); 
	static float DegreeToRadian(float degree);
	static float Angle(const sf::Vector2f& vec);

};