

#pragma once
#include "Core.hpp"
#include "Object.hpp"

namespace ly
{
struct TimerHandle
{
    TimerHandle();
    [[nodiscard]] unsigned int GetTimerKey() const { return mTimerKey; }
private:
    unsigned int mTimerKey;
    static unsigned int sm_TimerID;
    static unsigned int IncrementAndGetNextTimerKey() { return ++sm_TimerID; }
};

struct TimerHandleHashFunction
{
    std::size_t operator()(const TimerHandle& handle) const
    {
        return handle.GetTimerKey();
    }
};

inline bool operator==(const TimerHandle& lhs, const TimerHandle& rhs)
{
    return lhs.GetTimerKey() == rhs.GetTimerKey();
}
struct Timer
{
    Timer(const weak<Object>& weakRef, const std::function<void()>& callback, float duration, bool repeat);
    void TickTime(float deltaTime);
    [[nodiscard]] bool IsExpired() const;
    void SetExpired();
private:
    std::pair<weak<Object>, std::function<void()>> mListener;
    float mDuration;
    bool mRepeat;
    float mTimerCounter;
    bool mIsExpired;
};

class TimerManager 
{
public:
    static TimerManager& Get();
    template<typename ClassName>
    TimerHandle SetTimer(weak<Object> weakRef, void(ClassName::*callback)(), float duration, bool repeat = false)
    {
        TimerHandle newHandle{};
        mTimers.insert({newHandle, Timer{weakRef, [=]{(static_cast<ClassName*>(weakRef.lock().get())->*callback)(); }, duration, repeat}});
        return newHandle;
    }

    void UpdateTimer(float deltaTime);
    void ClearTimer(const TimerHandle timerHandle);

protected:
    TimerManager();
private:
    static unique<TimerManager> instance;
    static unsigned int timerIndexCount;
    Dictionary<TimerHandle, Timer, TimerHandleHashFunction> mTimers;
};

}
