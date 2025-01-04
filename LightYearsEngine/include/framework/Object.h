#pragma once

#include<memory>
#include"framework/core.h"
#include"framework/Delegate.h"

namespace ly
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual ~Object();

		virtual void Destroy();
		bool IsPendingDestroy() const { return mIsPendingDestroy; };

		weak<Object> GetWeakRef();
		weak<const Object>  GetWeakRef() const;

		DeLegate<Object*> onDestroy;
	

	private:
		bool mIsPendingDestroy;

	};
}