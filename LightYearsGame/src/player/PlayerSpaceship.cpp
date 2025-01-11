

#include "PlayerSpaceship.hpp"
#include "MathUtility.hpp"

namespace ly {
    PlayerSpaceship::~PlayerSpaceship()
    {
        LOG("Player Spaceship Destroyed");
    }

    PlayerSpaceship::PlayerSpaceship(const std::string &name, World *owningWorld, const std::string &path):
        Spaceship{name, owningWorld, path},
        mMoveInput{},
        mSpeed{200.0f},
        mShooter{std::make_unique<BulletShooter>(this, 0.20f, Vector2Df{50.0f, 0.0f}, 0.0f)},
        mInvulnerableTime{2.0f},
        mInvulnerableTimer{},
        mInvulnerable{true},
        mInvulnerableFlashInterval{0.5f},
        mInvulnerableFlashTimer{0.0f},
        mInvulnerableFlashDirection{1}

    {
        SetTeamId(1);
        // mShooter->SetCurrentLevelToMaxLevel(); // TEstiing
    }

    void PlayerSpaceship::Tick(const float deltaTime)
    {
        Spaceship::Tick(deltaTime);
        HandleInput();
        ConsumeInput(deltaTime);
        UpdateInvulnerable(deltaTime);
    }

    void PlayerSpaceship::SetSpeed(const float newSpeed)
    {
        mSpeed = newSpeed;
    }

    float PlayerSpaceship::GetSpeed() const
    {
        return mSpeed;
    }

    void PlayerSpaceship::Shoot()
    {
        if(mShooter)
        {
            mShooter->Shoot();
        }
    }

    void PlayerSpaceship::SetShooter(unique<Shooter> &&newShooter)
    {
        if(mShooter && typeid(*mShooter.get()) == typeid(*newShooter.get()))
        {
            mShooter->IncrementCurrentLevel(1);
            return;
        }
        mShooter = std::move(newShooter);
    }

    void PlayerSpaceship::ApplyDamage(float damage)
    {
        if(!mInvulnerable)
        {
            Spaceship::ApplyDamage(damage);
        }
    }

    void PlayerSpaceship::BeginPlay()
    {
        Spaceship::BeginPlay();
        TimerManager::Get().SetTimer(GetSelfWeakSRef(), &PlayerSpaceship::StopInvulnerable, mInvulnerableTime);
    }

    void PlayerSpaceship::StopInvulnerable()
    {
        GetSprite().setColor({255, 255, 255, 255});
        mInvulnerable = false;
    }

    void PlayerSpaceship::UpdateInvulnerable(float deltaTime)
    {
        if(!mInvulnerable)
        {
            return;
        }

        mInvulnerableFlashTimer += deltaTime * mInvulnerableTime;
        if(mInvulnerableFlashTimer < 0 || mInvulnerableFlashTimer > mInvulnerableFlashInterval)
        {
            mInvulnerableFlashDirection *= -1;
        }

        GetSprite().setColor(MathUtility::LerpColor({255, 255, 255, 64}, {255, 255, 255, 128}, mInvulnerableFlashTimer / mInvulnerableFlashInterval));

    }

    void PlayerSpaceship::HandleInput()
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            mMoveInput.SetY(-1.0f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            mMoveInput.SetY(1.0f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            mMoveInput.SetX(-1.0f);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            mMoveInput.SetX(1.0f);
        }
        ClampInputOnEdge();
        NormalizeInput();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Shoot();
        }
    }

    void PlayerSpaceship::NormalizeInput()
    {
        MathUtility::Normalize(mMoveInput);
        // LOG("Move input normalized: %f, %f", mMoveInput.x, mMoveInput.y);
    }

    void PlayerSpaceship::ClampInputOnEdge()
    {
        const Vector2Df actorLocation = GetActorLocation();
        if(actorLocation.GetX() < 0 && mMoveInput.GetX() == -1)
        {
            mMoveInput.SetX(0.0f);
        }
        if(actorLocation.GetX() > static_cast<float>(GetWidowSize().GetX()) && mMoveInput.GetX() == 1.0f)
        {
            mMoveInput.SetX(0.0f);
        }
        if(actorLocation.GetY() < 0 && mMoveInput.GetY() == -1)
        {
            mMoveInput.SetY(0.0f);
        }
        if(actorLocation.GetY() > static_cast<float>(GetWidowSize().GetY()) && mMoveInput.GetY() == 1.0f)
        {
            mMoveInput.SetY(0.0f);
        }

    }

    void PlayerSpaceship::ConsumeInput(float deltaTime)
    {
        SetVelocity(mMoveInput * mSpeed);
        mMoveInput.SetX(0.0f);
        mMoveInput.SetY(0.0f);
    }
}
