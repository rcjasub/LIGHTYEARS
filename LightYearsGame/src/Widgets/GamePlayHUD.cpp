#include "Widgets/GamePlayHUD.hpp"

namespace ly
{
	GamePlayHUD::GamePlayHUD()
		:mFrameText{"FrameRate:"}
	{
		mFrameText.SetTextSize(20);
	}

	void GamePlayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFrameText.NativeDraw(windowRef);
	}

	void GamePlayHUD::Tick(float deltaTime)
	{
		int frameRate = int(1 / deltaTime);
		std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
		mFrameText.SetString(frameRateStr);
	}
}