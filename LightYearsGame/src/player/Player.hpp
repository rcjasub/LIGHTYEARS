

#pragma once
#include "Object.hpp"

namespace ly
{
class PlayerSpaceship;
class Player: public Object
{
public:
    Player() = delete;
    explicit Player(const std::string& name);
    weak<PlayerSpaceship> SpawnPlayerSpaceship(World* world);
    const weak<PlayerSpaceship> GetCurrentPlayerSpaceship() const {return mCurrentPlayerSpaceship;};

    void AddLifeCount(unsigned int count);
    unsigned int GetLifeCount() const {return mPlayerLifeCount;}

    void AddScore(unsigned int amount);
    unsigned int GetScore() const { return mScore;}

    Delegate<int> onLifeChanged;
    Delegate<int> onScoreChanged;
    Delegate<> onLifeExhausted;
private:
    unsigned int mPlayerLifeCount;
    unsigned int mScore;
    weak<PlayerSpaceship> mCurrentPlayerSpaceship;

};

}
