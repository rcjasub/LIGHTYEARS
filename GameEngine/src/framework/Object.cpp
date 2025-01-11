#include "Object.hpp"
#include "Core.hpp"

namespace ly
{
    uint64_t Object::smUniqueID_counter{0};
    Object::Object(const std::string& name):
        mIsPendingDestroy{false},
        mUniqueID{GetNextAvailableID()},
        mName{name +"_"+ std::to_string(GetUniqueId())}
    {
    }
    Object::~Object()
    {
        LOG("%s Object Destroyed", mName.c_str());
    }

    void Object::Destroy()
    {
        OnDestroy.Broadcast(this);
        mIsPendingDestroy = true;
    }

    weak<Object> Object::GetSelfWeakSRef()
    {
        return weak_from_this();
    }

    weak<const Object> Object::GetSelfWeakSRef() const
    {
        return weak_from_this();
    }

    uint64_t Object::GetNextAvailableID()
    {
        return smUniqueID_counter++;
    }
}
