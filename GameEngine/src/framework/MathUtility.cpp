#include "framework/MathUtility.hpp"
#include<random>

namespace ly {

	const float pi = 3.1415926535;

	sf::Vector2f RotationVector(float rotation)
	{
		float radians = DegreesToRadiant(rotation);
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	float DegreesToRadiant(float degrees)
	{
		return degrees * (pi / 180.f);
	}

	float RadiantToDegrees(float radiant)
	{
		return radiant * (180.f / pi);
	}

	sf::Color lerpColor(const sf::Color& a, const sf::Color& b, float alpha)
	{
		int lerpR = lerpFloat(a.r, b.r, alpha);
		int lerpG = lerpFloat(a.g, b.g, alpha);
		int lerpB = lerpFloat(a.b, b.b, alpha);
		int lerpA = lerpFloat(a.a, b.a, alpha);

		return sf::Color(lerpR, lerpG, lerpB, lerpA);
	}

	sf::Vector2f lerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha)
	{
		float lerpX = lerpFloat(a.x, b.x, alpha);
		float lerpY = lerpFloat(a.y, b.y, alpha);

		return sf::Vector2f(lerpX, lerpY);
	}

	float lerpFloat(float a, float b, float alpha)
	{
		if (alpha > 1) alpha = 1;
		if (alpha < 0) alpha = 0;

		return a + (b - a) * alpha;
	}

	float RandomRange(float min, float max)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		std::uniform_real_distribution<float> distribution{ min, max };

		return distribution(gen);
	}
	sf::Vector2f RandomUnitVector()
	{
		float randomX = RandomRange(-1, 1);
		float randomY = RandomRange(-1, 1);

		sf::Vector2f randVec{ randomX, randomY };

		Normalize(randVec);
		
		return randVec;
	}
}