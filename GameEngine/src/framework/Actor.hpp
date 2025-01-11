#pragma once

#include "Object.hpp"
#include "Core.hpp"
#include <SFML/Graphics.hpp>
#include "Vector2D.hpp"

class b2Body;

namespace ly
{
    class World;
    class Actor: public Object
    {
        public:
            Actor() = delete;
            Actor(const std::string& name, World *owningWorld, const std::string &texturePath);
            ~Actor() override = default;

            void BeginPlayInternal();
            void TickInternal(const float deltaTime);
            virtual void BeginPlay();
            virtual void Tick(const float deltaTime);
            void SetTexture(const std::string &texturePath);
            virtual void Render(sf::RenderWindow& window) const;

            void SetActorLocation(const Vector2Df& newLoc);
            void SetActorRotation_degrees(float newRot_degrees);
            Vector2Df GetActorLocation() const;
            float GetActorRotation_rad() const;
            void AddActorLocationOffset(const Vector2Df& offSet);
            void AddActorRotationOffset(float newOffset);
            Vector2Df GetActorForwardDirection() const;
            Vector2Df GetActorRightDirection() const;
            sf::FloatRect GetActorGlobalBounds() const;
            bool IsActorOutOfWindowBounds(float allowance = 10.0f) const;

            Vector2Du GetWidowSize() const;
            World* GetWorld() { return mOwningWorld; }
            World* GetWorld() const { return mOwningWorld; }
            // World const* GetWorld() const { return mOwningWorld; } TODO: figure out why this doesn't work

            void SetEnablePhysics(bool enable);
            virtual void OnActorBeginOverlap(Actor * other);
            virtual void OnActorEndOverlap(Actor * other);

            void Destroy() override;
            static uint8 GetNeutralTeamId() { return s_nearestTeamId; }
            void SetTeamId(const uint8 id){ mTeamId = id; }
            uint8 GetTeamId() const {return mTeamId;}
            bool IsOtherHostile(Actor* other) const;
            virtual void ApplyDamage(float damage) {};

            sf::Sprite& GetSprite() {return mSprite;};
            const sf::Sprite& GetSprite() const {return mSprite;};
            void SetTextureRepeated(bool repeated) const;

            Delegate<Actor*> onActorDestroyed;
        private:
            void InitializePhysics();
            void UnInitializePhysics();
            void UpdatePhysicsBodyTransform() const;

            void CenterPivot();
            World* mOwningWorld;
            bool mHasBeganPlay;

            sf::Sprite mSprite;
            shared<sf::Texture> mTexture;

            b2Body* mPhysicsBody;
            bool mPhysicsEnabled;

            uint8 mTeamId;
            static constexpr uint8 s_nearestTeamId{255};
    };
}
