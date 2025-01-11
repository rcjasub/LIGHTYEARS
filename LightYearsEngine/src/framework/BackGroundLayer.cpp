
#include "BackGroundLayer.hpp"
#include "AssetManager.hpp"
#include "MathUtility.hpp"
#include "World.hpp"

namespace ly {
    BackGroundLayer::BackGroundLayer(
        World *owning,
        const List<std::string>& assetPaths,
        const Vector2Df &minVelocity,
        const Vector2Df &maxVelocity,
        float sizeMin, float sizeMax,
        unsigned int spriteCount,
        const sf::Color &tintColor) :
    Actor{"BackGroundLayer", owning, ""},
    mMinVelocity{minVelocity},
    mMaxVelocity{maxVelocity},
    mSizeMin{sizeMin},
    mSizeMax{sizeMax},
    mSprintCount{spriteCount},
    mTintColor{tintColor}
    {
        SetEnablePhysics(false);
    }

    void BackGroundLayer::SetAssets(const List<std::string>& assetPaths)
    {
        for (const std::string& assetPath : assetPaths)
        {
            shared<sf::Texture> newTexture = AssetManager::Get().LoadTexture(assetPath);
            mTextures.emplace_back(newTexture);
        }
        RefreshSprites();
    }

    void BackGroundLayer::RefreshSprites()
    {
        mSprites.clear();
        mVelocities.clear();

        for(int i = 0; i < mSprintCount; i++)
        {
            sf::Sprite newSprite{};
            RandomSpriteTexture(newSprite);
            RandomSpriteTransform(newSprite, true);
            mSprites.emplace_back(newSprite);

            float velX{MathUtility::RandomRange(mMinVelocity.GetX(), mMaxVelocity.GetX())};
            float velY{MathUtility::RandomRange(mMinVelocity.GetY(), mMaxVelocity.GetY())};
            mVelocities.emplace_back(velX, velY);
        }

        SetColorTint(mTintColor);
    }

    void BackGroundLayer::RandomSpriteTexture(sf::Sprite &sprite) const
    {
        if(!mTextures.empty())
        {
            shared<sf::Texture> pickedTexture{GetRandomTexture()};
            sprite.setTexture(*(pickedTexture.get()));
            sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(pickedTexture->getSize().x), static_cast<int>(pickedTexture->getSize().y)));
            sf::FloatRect bounds{sprite.getGlobalBounds()};
            sprite.setOrigin(bounds.width / 2, bounds.height / 2);
        }
    }

    void BackGroundLayer::RandomSpriteTransform(sf::Sprite &sprite, bool randomY) const
    {
        RandomSpritePosition(sprite, randomY);
        RandomSpriteRotation(sprite);
        RandomSpriteSize(sprite);
    }

    void BackGroundLayer::RandomSpritePosition(sf::Sprite &sprite, bool randomY) const
    {
        const auto windowSize{GetWorld()->GetWindowSize()};
        const auto bound{sprite.getGlobalBounds()};

        const float posY{MathUtility::RandomRange(0.0, static_cast<float>(windowSize.GetX()))};
        const float posX{randomY ? MathUtility::RandomRange(0.0, static_cast<float>(windowSize.GetY())) : -bound.height};

        sprite.setPosition(posX, posY);
    }

    void BackGroundLayer::RandomSpriteRotation(sf::Sprite &sprite) const
    {
        sprite.setRotation(MathUtility::RandomRange(0, 360));
    }

    void BackGroundLayer::RandomSpriteSize(sf::Sprite &sprite) const
    {
        const float size{MathUtility::RandomRange(mSizeMin, mSizeMax)};
        sprite.setScale(size, size);
    }

    void BackGroundLayer::SetColorTint(const sf::Color &color)
    {
        mTintColor = color;
        for(sf::Sprite& sprite : mSprites)
        {
            sprite.setColor(color);
        }
    }

    void BackGroundLayer::SetSpriteCount(const unsigned int spriteCount)
    {
        mSprintCount = spriteCount;
        RefreshSprites();
    }

    void BackGroundLayer::SetVelocities(const Vector2Df &min, const Vector2Df &max)
    {
        mMinVelocity = min;
        mMaxVelocity = max;

        for(int i = 0; i < mSprites.size(); i++)
        {
            const float velX{MathUtility::RandomRange(mMinVelocity.GetX(), mMaxVelocity.GetX())};
            const float velY{MathUtility::RandomRange(mMinVelocity.GetY(), mMaxVelocity.GetY())};
            mVelocities[i] = Vector2D(velX, velY);
        }
    }

    void BackGroundLayer::SetSizes(float min, float max)
    {
        mSizeMin = min;
        mSizeMax = max;

        for(int i = 0; i < mSprites.size(); i++)
        {
            RandomSpriteSize(mSprites[i]);
        }
    }

    void BackGroundLayer::Render(sf::RenderWindow &window) const
    {
        // Actor::Render(window); // todo - ??
        for(const auto &sprite : mSprites)
        {
            window.draw(sprite);
        }
    }

    bool BackGroundLayer::IsSpriteOffScreen(const sf::Sprite &sprite) const
    {
        const auto bounds{sprite.getGlobalBounds()};
        const auto windowSize{GetWorld()->GetWindowSize()};
        const auto pos{sprite.getPosition()};

        if(pos.x < -bounds.width || pos.x > static_cast<float>(windowSize.GetX()) + bounds.width)
        {
            return true;
        }
        if(pos.y < -bounds.height || pos.y > static_cast<float>(windowSize.GetY()) + bounds.height)
        {
            return true;
        }

        return false;

    }

    void BackGroundLayer::Tick(const float deltaTime)
    {
        Actor::Tick(deltaTime);
        // for(const auto &sprite : mSprites)
        for(int i = 0; i < mSprites.size(); i++)
        {
            sf::Sprite& sprite {mSprites[i]};
            Vector2Df& vel{mVelocities[i]};

            sprite.setPosition(sprite.getPosition() + sf::Vector2f{vel.GetX(), vel.GetY()} * deltaTime);
            if(IsSpriteOffScreen(sprite))
            {
                RandomSpriteTransform(sprite);
                RandomSpriteTexture(sprite);
                float velX{MathUtility::RandomRange(mMinVelocity.GetX(), mMaxVelocity.GetX())};
                float velY{MathUtility::RandomRange(mMinVelocity.GetY(), mMaxVelocity.GetY())};
                mVelocities.emplace_back(velX, velY);
            }
        }
    }

    shared<sf::Texture> BackGroundLayer::GetRandomTexture() const
    {
        const auto randomIndex = static_cast<unsigned int>(MathUtility::RandomRange(0.0f, static_cast<float>(mTextures.size() - 1)));
        return mTextures[randomIndex];
    }
}
