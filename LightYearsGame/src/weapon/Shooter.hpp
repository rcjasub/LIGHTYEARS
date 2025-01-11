
#pragma once

namespace ly
{
    class Actor;
    class Shooter
    {
    public:
        virtual ~Shooter() = default;

        void Shoot();
        [[nodiscard]] virtual bool CanShoot() const {return true;}
        [[nodiscard]] virtual bool IsOnCooldown() const {return false;}
        [[nodiscard]] Actor const* const GetOwner() const {return mOwner;}

        [[nodiscard]] unsigned int GetCurrentLevel() const {return mCurrentLevel;}
        [[nodiscard]] unsigned int GetMaxLevel() const {return mMaxLevel;}

        virtual void IncrementCurrentLevel(unsigned int level);
        virtual void SetCurrentLevel(unsigned int level);
        virtual void SetCurrentLevelToMaxLevel() {mCurrentLevel = mMaxLevel;} // todo fix that frontal wiper still increases after max level
        virtual void SetMaxLevel(const unsigned int level) {mMaxLevel = level;}
    protected:
        explicit Shooter(const Actor* owner, unsigned int currentLevel = 1, unsigned int maxLevel = 4);
    private:
        virtual void ShootImpl() = 0;
        Actor const* const mOwner;

        unsigned int mCurrentLevel;
        unsigned int mMaxLevel;
    };

}
