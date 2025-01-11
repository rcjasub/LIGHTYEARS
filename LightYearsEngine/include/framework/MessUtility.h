#pragma once
#include<SFML/Graphics.hpp>
#include <cmath>

namespace ly
{
	sf::Vector2f RotationVector(float rotation);
	float DegreesToRadiant(float degrees);
	float RadiantToDegrees(float radiant);

	template<typename T>
	float getVectorLength(const sf::Vector2<T>& vector)
	{
		return std::sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	template<typename T>
	sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vectorToScale, float amt)
	{
		vectorToScale.x *= amt;
		vectorToScale.y *= amt;

		return vectorToScale;
	}

	template<typename T>
	sf::Vector2<T> Normalize(sf::Vector2<T>& vector)
	{
		float vectorLength = getVectorLength<T>(vector);

		if (vectorLength == 0.f)  return sf::Vector2<T>{};

		ScaleVector(vector, 1.0 / vectorLength);

		return vector;
	}

	sf::Color lerpColor(const sf::Color& a, const sf::Color& b, float alpha);

	sf::Vector2f lerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha);

	float lerpFloat(float a, float b, float alpha);

	float RandomRange(float min, float max);
	sf::Vector2f RandomUnitVector();
}
