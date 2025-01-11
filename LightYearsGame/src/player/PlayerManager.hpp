

#pragma once
#include "Core.hpp"
#include "Player.hpp"

namespace ly
{

class PlayerManager 
{
public:
    static PlayerManager& GetInstance();
    Player* CreateNewPlayer();
    Player* GetPlayer(unsigned int playerIndex = 0);
    void Reset();
protected:
    PlayerManager() = default;

private:
    List<Player> mPlayers;
    static unique<PlayerManager> instance;
};

}