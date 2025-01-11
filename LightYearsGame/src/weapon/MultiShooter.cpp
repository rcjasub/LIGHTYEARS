//
// Created by wbowen on 11/9/24.
//

#include "MultiShooter.hpp"

namespace ly {
    MultiShooter::MultiShooter(const std::initializer_list<BulletShooter> shooters):
        mShooters{shooters}
    {
    }

    void MultiShooter::ShootAll()
    {
        for(auto& shooter: mShooters)
        {
            shooter.Shoot();
        }
    }

    void MultiShooter::IncrementLevelAll(unsigned int amount)
    {
        for(auto& shooter: mShooters)
        {
            shooter.IncrementCurrentLevel(amount);
        }
    }

    void MultiShooter::SetCurrentLevel(unsigned level)
    {
        for(auto& shooter: mShooters)
        {
            shooter.SetCurrentLevel(level);
        }
    }
}
