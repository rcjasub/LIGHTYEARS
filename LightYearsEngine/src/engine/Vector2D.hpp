

#pragma once
#include <iostream>

namespace ly
{

template <typename T>
class Vector2D
{
public:
    static const Vector2D& Zero;

    Vector2D();
    Vector2D(const T x, const T y);

    [[nodiscard]] inline T GetX() const { return mX; }
    [[nodiscard]] inline T GetY() const { return mY; }
    void SetX(const T x) { mX = x; }
    void SetY(const T y) { mY = y; }

    Vector2D operator+(const Vector2D& rhs) const;
    Vector2D operator-(const Vector2D& rhs) const;
    Vector2D operator*(const T rhs) const;
    Vector2D operator/(const T rhs) const;
    Vector2D& operator+=(const Vector2D& rhs);
    Vector2D& operator-=(const Vector2D& rhs);
    Vector2D& operator*=(const T rhs);
    Vector2D& operator/=(const T rhs);

    bool operator==(const Vector2D& rhs) const;
    void Display() const;
private:
    T mX, mY;

};

using Vector2Du = Vector2D<unsigned int>;
using Vector2Di = Vector2D<int>;
using Vector2Df = Vector2D<float>;
using Vector2Dd = Vector2D<double>;

template <typename T>
Vector2D<T>::Vector2D(): Vector2D<T>{T{0}, T{0}}
{

}

template <typename T>
Vector2D<T>::Vector2D(const T x, const T y) : mX{x}, mY{y}
{

}

template <typename T>
Vector2D<T> Vector2D<T>::operator+(const Vector2D &rhs) const
{
    return Vector2D{mX + rhs.mX, mY + rhs.mY};
}

template <typename T>
Vector2D<T> Vector2D<T>::operator-(const Vector2D &rhs) const
{
    return Vector2D{mX - rhs.mX, mY - rhs.mY};
}

template <typename T>
Vector2D<T> Vector2D<T>::operator*(const T rhs) const
{
    return Vector2D{mX * rhs, mY * rhs};
}

template <typename T>
Vector2D<T> Vector2D<T>::operator/(const T rhs) const
{
    return Vector2D{mX / rhs, mY / rhs};
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator+=(const Vector2D &rhs)
{
    mX += rhs.mX;
    mY += rhs.mY;
    return *this;
}

template <typename T>
Vector2D<T>& Vector2D<T>::operator-=(const Vector2D &rhs)
{
    mX -= rhs.mX;
    mY -= rhs.mY;
    return *this;
}

template<typename T>
Vector2D<T> & Vector2D<T>::operator*=(const T rhs)
{
    mX *= rhs;
    mY *= rhs;
    return *this;
}

template<typename T>
Vector2D<T> & Vector2D<T>::operator/=(const T rhs)
{
    mX /= rhs;
    mY /= rhs;
    return *this;
}

template <>
inline bool Vector2D<float>::operator==(const Vector2D &rhs) const
{
    static float epsilon{0.001};

    const auto xComp{mX <= rhs.mX + epsilon && mX >= rhs.mX - epsilon};
    const auto yComp{mY <= rhs.mY + epsilon && mY >= rhs.mY - epsilon};
    return xComp && yComp;
}

template<typename T>
bool Vector2D<T>::operator==(const Vector2D &rhs) const
{
    return mX == rhs.mX && mY == rhs.mY;
}

template <typename T>
void Vector2D<T>::Display() const
{
    std::cout << "X: " << mX << " Y: " << mY << std::endl;
}
}
