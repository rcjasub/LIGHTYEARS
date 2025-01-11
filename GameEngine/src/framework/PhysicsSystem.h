#pragma once 

#include <box2d/b2_world.h>
#include "framework/core.h"
#include "framework/core.h"


namespace ly
{
	class Actor;
	class PhysicsContactListener : public b2ContactListener
	{
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	}; 

	class PhysicsSystem
	{
	public:

		static PhysicsSystem& Get();
		void Step(float deltaTime);
		b2Body* addListener(Actor* listener);
		void removeListener(b2Body* bodyToRemove);
		float GetPhysicsScale() const { return mPhysicsScale; }

		static void CleanUp();

	protected:
		PhysicsSystem();

	private:
		void ProcessPendingRemoveListener();

		static unique<PhysicsSystem> physicsSystem;

		b2World mPhysicsWorld;
		float mPhysicsScale;
		int mVelocityIterations;
		int mPositionIterations;

		PhysicsContactListener mContactListener;

		Set<b2Body* >mPendingRemoveListener;

	};
}