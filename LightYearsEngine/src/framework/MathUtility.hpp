

#pragma once

#include <cmath>
#include <Vector2D.hpp>
#include <SFML/Graphics/Color.hpp>

namespace ly
{
    class MathUtility {
    public:
        static Vector2Df RotationToVector(float rotation);
        static float DegreesToRadians(float degrees);  //todo figure out whether this is actually degrees or radians, something fishy in use cases
        static float RadiansToDegrees(float radians);  //todo figure out whether this is actually degrees or radians, something fishy in use cases

        template<typename T>
        static float GetVectorLength(const Vector2D<T>& vector)
        {
            return std::sqrt(vector.GetX() * vector.GetX() + vector.GetY() * vector.GetY());
        }

        template<typename T>
        static Vector2D<T>& ScaleVector(Vector2D<T>& vectorToScale, float amt)
        {
            vectorToScale *= amt;
            return vectorToScale;
        }

        template<typename T>
        static Vector2D<T>& Normalize(Vector2D<T>& vector)
        {
            const float vectorLength {GetVectorLength<T>(vector)};
            if (vectorLength == 0.0f) {
                return vector;
            }
            ScaleVector(vector, 1.0f / vectorLength);
            return vector;
        }

        static sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha);
        static Vector2Df LerpVector(const Vector2Df& a, const Vector2Df& b, float alpha);
        static float LerpFloat(float a, float b, float alpha);
        static float RandomRange(float min, float max);
        static Vector2Df RandomUnitVector();
        static bool NumberInRangeExclusive(float value, float lo, float high);
        static bool NumberInRangeInclusive(float value, float lo, float high, float epsilon);
    };
}
