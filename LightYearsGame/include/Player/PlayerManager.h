#pragma once 

#include "framework/core.h"
#include "Player/Player.h"

namespace ly
{
	class PlayerManager
	{
	public:

		Player& CreateNewPlayer();
		Player* GetPlayer(int Playerindex = 0);
		const Player* GetPlayer(int Playerindex = 0) const;

		static PlayerManager& Get();

	protected:
		PlayerManager();

	private:
		list<Player> mPlayers;
		static unique<PlayerManager> mPlayerManager;
		
	};
}