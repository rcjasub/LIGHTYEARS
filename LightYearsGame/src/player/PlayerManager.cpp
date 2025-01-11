//
// Created by wbowen on 11/15/24.
//

#include "PlayerManager.hpp"

namespace ly
{
    unique<PlayerManager> PlayerManager::instance{nullptr};
    PlayerManager & PlayerManager::GetInstance()
    {
        if (instance == nullptr)
        {
            // instance = std::move(std::make_unique<PlayerManager>());
            unique<PlayerManager> playerManagerInstance(new PlayerManager());
            instance = std::move(playerManagerInstance);
        }

        return *instance;
    }

Player* PlayerManager::CreateNewPlayer()
{
    Player newPlayer{"Player"};
    // mPlayers.emplace(mPlayers.begin(), std::move(newPlayer)); //todo - determine why this doesn't work
    mPlayers.emplace_back(std::move(newPlayer));
    return &mPlayers.front();
}

Player* PlayerManager::GetPlayer(const unsigned int playerIndex)
{
    if (playerIndex >= 0 && playerIndex < mPlayers.size())
    {
        return &mPlayers[playerIndex];
    }
    return nullptr;
}

void PlayerManager::Reset()
{
    mPlayers.clear();
}
}
