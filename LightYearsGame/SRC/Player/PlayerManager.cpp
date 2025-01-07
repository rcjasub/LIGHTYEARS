#include "Player/PlayerManager.h"

namespace ly
{
	unique<PlayerManager> PlayerManager::mPlayerManager{ nullptr };

	PlayerManager::PlayerManager()
	{
	}

	Player& PlayerManager::CreateNewPlayer()
	{
		mPlayers.emplace(mPlayers.begin(), Player());
		return mPlayers.back();
	}

	Player* PlayerManager::GetPlayer(int Playerindex)
	{
		if (Playerindex >= 0 && Playerindex <= mPlayers.size())
		return &(mPlayers[Playerindex]);
		return nullptr;
	}

	const Player* PlayerManager::GetPlayer(int Playerindex) const
	{
		if (Playerindex >= 0 && Playerindex < mPlayers.size())  // Fix bounds check
			return &(mPlayers[Playerindex]);
		return nullptr;
	}

	PlayerManager& PlayerManager::Get()
	{
		if (!mPlayerManager)
		{
			mPlayerManager = std::move(unique<PlayerManager>{new PlayerManager{}});
		}

		return *mPlayerManager;
	}

}