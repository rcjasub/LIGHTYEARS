#include"framework/Object.hpp"
#include"framework/core.hpp"

namespace ly
{
	 Object::Object()
		: mIsPendingDestroy{false}
	{
	}

	Object::~Object()
	{
		LOG("Objected Destroy");
	}

	void Object::Destroy()
	{
		onDestroy.BroadCast(this);
		mIsPendingDestroy = true;
	}

	weak<Object> Object::GetWeakRef() 
	{
		return weak_from_this();
	}

	weak<const Object> Object::GetWeakRef() const
	{
		return weak_from_this();
	}

}