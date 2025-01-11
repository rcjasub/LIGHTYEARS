
#include "PhysicsSystem.hpp"
#include "Actor.hpp"
#include "MathUtility.hpp"
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>

namespace ly
{
    unique<PhysicsSystem> PhysicsSystem::s_mPhysicsSystem{nullptr};

    void PhysicsContactListener::BeginContact(b2Contact *contact)
    {
        // LOG("Contact begin");
        const auto ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        const auto ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        if(ActorA && !ActorA->IsPendingDestroy())
        {
            ActorA->OnActorBeginOverlap(ActorB);
        }

        if(ActorB && !ActorB->IsPendingDestroy())
        {
            ActorB->OnActorBeginOverlap(ActorA);
        }
    }

    void PhysicsContactListener::EndContact(b2Contact *contact)
    {
        // LOG("Contact end");
        Actor* ActorA{nullptr};
        Actor* ActorB{nullptr};

        if(contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
        {
            ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        }

        if(contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
        {
            ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        }

        if(ActorA && !ActorA->IsPendingDestroy())
        {
            ActorA->OnActorEndOverlap(ActorB);
        }

        if(ActorB && !ActorB->IsPendingDestroy())
        {
            ActorB->OnActorEndOverlap(ActorA);
        }
    }

    void PhysicsSystem::Cleanup()
    {
        s_mPhysicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
    }

    PhysicsSystem::PhysicsSystem():
        mPhysicsWorld{b2Vec2{0.0f,0.0f}},
        mPhysicsScale{0.01f},
        mVelocityIterations{8},
        mPositionIterations{3},
        mContactListener{},
        mPendingRemoveListener{}
    {
        mPhysicsWorld.SetContactListener(&mContactListener);
        mPhysicsWorld.SetAllowSleeping(false);
    }

    void PhysicsSystem::ProcessPendingRemoveListener()
    {
        for(const auto listener : mPendingRemoveListener)
        {
            mPhysicsWorld.DestroyBody(listener);
        }
        mPendingRemoveListener.clear();
    }

    PhysicsSystem & PhysicsSystem::GetInstance()
    {
        if(!s_mPhysicsSystem)
        {
            // s_mPhysicsSystem = std::move(std::make_unique<PhysicsSystem>());
            // Todo - enable singleton creation of class with private/protected constructor
            s_mPhysicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
        }

        return *s_mPhysicsSystem;
    }

    void PhysicsSystem::Step(const float deltaTime)
    {
        ProcessPendingRemoveListener();
        mPhysicsWorld.Step(deltaTime, mVelocityIterations, mPositionIterations);
    }

    b2Body * PhysicsSystem::AddListener(Actor *listener)
    {
        if(listener)
        {
            if(listener->IsPendingDestroy()) return nullptr;

            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;

            bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);

            bodyDef.position.Set(listener->GetActorLocation().GetX() * GetPhysicsScale(), listener->GetActorLocation().GetY() * GetPhysicsScale());
            bodyDef.angle = MathUtility::DegreesToRadians(listener->GetActorRotation_rad());

            b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);

            b2PolygonShape shape;
            const auto bound = listener->GetActorGlobalBounds();
            shape.SetAsBox(bound.width/2.0f * GetPhysicsScale(), bound.height/2.0f * GetPhysicsScale());

            b2FixtureDef fixture;
            fixture.shape = &shape;
            fixture.density = 1.0f;
            fixture.friction = 0.3f;
            fixture.isSensor = true;

            body->CreateFixture(&fixture);

            return body;
        }

        throw std::runtime_error("Could not add listener - Actor Null");
    }

    void PhysicsSystem::RemoveListener(b2Body *bodyToRemove)
    {
        mPendingRemoveListener.insert(bodyToRemove);
    }
}
