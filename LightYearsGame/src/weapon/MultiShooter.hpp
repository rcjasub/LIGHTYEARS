#pragma once

#include <initializer_list>
#include <vector>

#include "BulletShooter.hpp"

namespace ly
{

class MultiShooter
{
public:
    MultiShooter(const std::initializer_list<BulletShooter> shooters); //todo construct by reference
    ~MultiShooter() = default;

    void ShootAll();
    void IncrementLevelAll(unsigned int amount);
    void SetCurrentLevel(unsigned level);
private:
    std::vector<BulletShooter> mShooters;
};

}

