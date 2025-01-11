//
// Created by wbowen on 11/15/24.
//

#include "HUD.hpp"

namespace ly {
    HUD::HUD(const std::string& name):
        Object{name},
        mIsInitialized{false}
    {
    }

    void HUD::Tick(float deltaTime)
    {
    }

    void HUD::NativeInit(sf::RenderWindow &windowRef)
    {
        if(!mIsInitialized)
        {
            mIsInitialized = true;
            Init(windowRef);
        }
    }

    bool HUD::HandleEvent(const sf::Event &event)
    {
        return false;
    }
}