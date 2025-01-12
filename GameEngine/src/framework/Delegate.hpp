#pragma once

#include<functional>

#include "framework/core.hpp"


namespace ly
{
	class Object;

	template<typename... Args>

	class DeLegate
	{
	public:
        template<typename ClassName>

		void BindAction(weak<Object> obj, void(ClassName::* callBack)(Args...))
		{
			std::function<bool(Args...)> callBackFunction = [obj, callBack](Args...  args)->bool
				{
					if (!obj.expired())
					{
						(static_cast<ClassName*>(obj.lock().get())->*callBack)(args...);
						return true;
					}

					return false;
				};

			mCallBack.push_back(callBackFunction);
		}

		void BroadCast(Args...  args)
		{
			for (auto iter = mCallBack.begin(); iter != mCallBack.end();)
			{
				if ((*iter)(args...))
				{
					++iter;
				}
				
				else
				{
					iter = mCallBack.erase(iter);
				}
			}

		}

	private:

		list<std::function<bool(Args...)>> mCallBack;

	};

}