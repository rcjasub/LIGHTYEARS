
#pragma once

#include "Core.hpp"
#include <box2d/b2_world.h>
// Including for Actor.hpp
#include <box2d/b2_body.h>

namespace ly
{
    class Actor;

    class PhysicsContactListener final : public b2ContactListener
    {
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
    };

    class PhysicsSystem
    {
    public:
        ~PhysicsSystem() = default;

        static PhysicsSystem& GetInstance();
        void Step(float deltaTime);
        b2Body* AddListener(Actor* listener);
        void RemoveListener(b2Body* bodyToRemove);

        float GetPhysicsScale() const {return mPhysicsScale;}
        static void Cleanup();

    protected:
        PhysicsSystem();

    private:
        void ProcessPendingRemoveListener();

        static unique<PhysicsSystem> s_mPhysicsSystem;
        b2World mPhysicsWorld;
        float mPhysicsScale;
        int mVelocityIterations;
        int mPositionIterations;
        PhysicsContactListener mContactListener;

        Set<b2Body*> mPendingRemoveListener;
    };

}
