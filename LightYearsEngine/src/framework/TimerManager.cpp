
#include"framework/TimerManager.h"

namespace ly
{
	unsigned int TimerHandle::timerKeyCounter = 0;

	//class

	unique<TimerManager> TimerManager::timeManger{ nullptr };

	void TimerManager::UpdateTimer(float deltaTime)
	{
		for (auto iter = mTimers.begin(); iter != mTimers.end();)
		{
			if (iter->second.Expired())
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

	void TimerManager::ClearTimer(TimerHandle TimerHandle)
	{
		auto iter = mTimers.find(TimerHandle);

		if (iter != mTimers.end())
		{
			iter->second.SetExpired();
		}
	}

	TimerManager::TimerManager() : mTimers{}
	{}

	TimerManager& TimerManager::Get()
	{
		if (!timeManger)
		{
			timeManger = std::move(unique<TimerManager>(new TimerManager{}));
		}

		return *timeManger;
	}

	//Struct

	Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
		:mlistener{ weakRef, callback },
		mDuration{ duration },
		mRepeat{ repeat },
		mTimerCounter{ 0.f },
		mIsExpired{ false }

	{
	}

	void Timer::TickTime(float deltaTime)
	{
		if (Expired())
		{
			return;
		}

		mTimerCounter += deltaTime;
		if (mTimerCounter >= mDuration)
		{
			mlistener.second();

			if (mRepeat)
			{
				mTimerCounter = 0.f;
			}
			else
			{
				SetExpired();
			}
		}
	}

	bool Timer::Expired() const
	{
		return mIsExpired || mlistener.first.expired() || mlistener.first.lock()->IsPendingDestroy();
	}

	void Timer::SetExpired()
	{
		mIsExpired = true;
	}

	//struct

	TimerHandle::TimerHandle()
		:mTimerKey{GetNextTimerKey()}
	{
	}

	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs)
	{
		return lhs.GetTimerKey() == rhs.GetTimerKey();
	}
}