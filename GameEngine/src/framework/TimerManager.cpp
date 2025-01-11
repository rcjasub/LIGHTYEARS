

#include "TimerManager.hpp"

namespace ly
{
    unique<TimerManager> TimerManager::instance{nullptr};

    unsigned int TimerManager::timerIndexCount{0};

    void TimerManager::UpdateTimer(const float deltaTime)
    {
        for(auto iter =  mTimers.begin(); iter != mTimers.end();)
        {
            if(iter->second.IsExpired())
            {
                iter = mTimers.erase(iter);
            }
            else
            {
                iter->second.TickTime(deltaTime);
                ++iter;
            }
        }

    }

    void TimerManager::ClearTimer(const TimerHandle timerHandle)
    {
        if(const auto searchResult{mTimers.find(timerHandle)}; searchResult != mTimers.end())
        {
            searchResult->second.SetExpired();
        }
        else
        {
            LOG("Timer %d Not Found!!!", timerHandle.GetTimerKey());
        }
    }

    TimerManager::TimerManager() = default;

    unsigned int TimerHandle::sm_TimerID{0};

    TimerHandle::TimerHandle():
        mTimerKey(IncrementAndGetNextTimerKey())
    {
    }

    Timer::Timer(const weak<Object>& weakRef, const std::function<void()>& callback, const float duration, const bool repeat):
        mListener{weakRef, callback},
        mDuration{duration},
        mRepeat{repeat},
        mTimerCounter{0.0f},
        mIsExpired{false}
    {
    }

    void Timer::TickTime(const float deltaTime)
    {
        if(IsExpired())
        {
            return;
        }

        mTimerCounter += deltaTime;
        if(mTimerCounter >= mDuration)
        {
            mListener.second();

            if(mRepeat)
            {
                mTimerCounter = 0.0f;
            }
            else
            {
                SetExpired();
            }
        }
    }

    bool Timer::IsExpired() const
    {
        return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroy();
    }

    void Timer::SetExpired()
    {
        mIsExpired = true;
    }

    TimerManager& TimerManager::Get()
    {
        if(!instance)
        {
            // instance = std::make_unique<TimerManager>();
            instance = std::unique_ptr<TimerManager>(new TimerManager());
        }
        return *instance.get();
    }
}
