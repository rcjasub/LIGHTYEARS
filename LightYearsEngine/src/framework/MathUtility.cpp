
#include "MathUtility.hpp"
#include <random>

namespace ly
{
    Vector2Df MathUtility::RotationToVector(const float rotation)
    {
        const float radians = DegreesToRadians(rotation);
        return Vector2D{std::cos(radians), std::sin(radians)};
    }

    float MathUtility::DegreesToRadians(const float degrees)
    {
        return degrees * (static_cast<float>(M_PI) / 180.0f);
    }

    float MathUtility::RadiansToDegrees(const float radians)
    {
        return radians * (180.0f / static_cast<float>(M_PI));
    }

    sf::Color MathUtility::LerpColor(const sf::Color &a, const sf::Color &b, const float alpha)
    {
        const auto lerpR = LerpFloat(a.r, b.r, alpha);
        const auto lerpG = LerpFloat(a.g, b.g, alpha);
        const auto lerpB = LerpFloat(a.b, b.b, alpha);
        const auto lerpA = LerpFloat(a.b, b.a, alpha);

        return sf::Color{static_cast<unsigned char>(lerpR), static_cast<unsigned char>(lerpG), static_cast<unsigned char>(lerpB), static_cast<unsigned char>(lerpA)};

    }

    Vector2Df MathUtility::LerpVector(const Vector2Df &a, const Vector2Df &b, float alpha)
    {
        const auto lerpX = LerpFloat(a.GetX(), b.GetX(), alpha);
        const auto lerpY = LerpFloat(a.GetY(), b.GetY(), alpha);

        return Vector2D{lerpX, lerpY};
    }

    float MathUtility::LerpFloat(const float a, const float b, float alpha)
    {
        if(alpha > 1) alpha = 1;
        if(alpha < 0) alpha = 0;

        return a + (b - a) * alpha;
    }

    float MathUtility::RandomRange(float min, float max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<float> distribution{min, max};

        return distribution(gen);
    }

    Vector2Df MathUtility::RandomUnitVector()
    {
        const float randomX = RandomRange(-1.0f, 1.0f);
        const float randomY = RandomRange(-1.0f, 1.0f);

        Vector2D randomVec{randomX, randomY};
        Normalize(randomVec);
        return  randomVec;
    }

    bool MathUtility::NumberInRangeExclusive(const float value, const float lo, const float high)
    {
        if(value > high) return false;
        if(value < lo) return false;
        return true;
    }

    bool MathUtility::NumberInRangeInclusive(const float value, const float lo, const float high, const float epsilon)
    {
        if(value > (high - epsilon)) return false;
        if(value < (lo + epsilon)) return false;
        return true;
    }
}
