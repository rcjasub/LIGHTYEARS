

#pragma once
#include "Core.hpp"
#include <functional>

namespace ly
{
    class Object;
    template<typename... Args>
    class Delegate
    {
    public:
        template<typename ClassName>
        void BindAction(weak<Object> obj, void(ClassName::*callback)(Args...));
        void Broadcast(Args... args);
    private:
        List<std::function<bool(Args...)>> mCallbacks;

    };

    template<typename ... Args>
    template<typename ClassName>
    void Delegate<Args...>::BindAction(weak<Object> obj, void(ClassName::*callback)(Args...))
    {
        std::function<bool(Args...)> callbackFunc = [obj, callback](Args... args)->bool
        {
            if(!obj.expired())
            {
                (static_cast<ClassName*>(obj.lock().get())->*callback)(args...);
                return true;
            }
            return false;
        };

        mCallbacks.push_back(callbackFunc);
    }

    template<typename ... Args>
    void Delegate<Args...>::Broadcast(Args... args)
    {
        for(auto iter = mCallbacks.begin(); iter != mCallbacks.end();)
        {
            if((*iter)(args...))
            {
                ++iter;
            }
            else
            {
                iter = mCallbacks.erase(iter);
            }
        }
    }
}
