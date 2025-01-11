

#pragma once
#include "Actor.hpp"

namespace ly
{

class BackGroundLayer : public Actor
{
public:
    explicit BackGroundLayer(World* owning,
                    const List<std::string>& assetPaths = {},
                    const Vector2Df& minVelocity = Vector2Df{0.0f, 50.0f},
                    const Vector2Df& maxVelocity = Vector2Df{0.0f, 200.0f},
                    float sizeMin = 1.0f,
                    float sizeMax = 2.0f,
                    unsigned int spriteCount = 20,
                    const sf::Color& colorTint = sf::Color{180, 180, 200, 255}
                    );

    void SetAssets(const List<std::string>& assetPaths);
    void SetColorTint(const sf::Color& color);
    void SetSpriteCount(unsigned int spriteCount);
    void SetVelocities(const Vector2Df& min, const Vector2Df& max);
    void SetSizes(float min, float max);

    void Render(sf::RenderWindow &window) const override;
    bool IsSpriteOffScreen(const sf::Sprite & sprite) const;
    void Tick(const float deltaTime) override;
private:
    void RefreshSprites();
    void RandomSpriteTexture(sf::Sprite& sprite) const;
    void RandomSpriteTransform(sf::Sprite& sprite, bool randomY = false) const;
    void RandomSpritePosition(sf::Sprite& sprite, bool randomY = false) const;
    void RandomSpriteRotation(sf::Sprite& sprite) const;
    void RandomSpriteSize(sf::Sprite& sprite) const;
    shared<sf::Texture> GetRandomTexture() const;
    Vector2Df mMinVelocity;
    Vector2Df mMaxVelocity;
    float mSizeMin;
    float mSizeMax;
    unsigned int mSprintCount;
    sf::Color mTintColor;

    List<shared<sf::Texture>> mTextures;
    List<sf::Sprite> mSprites;
    List<Vector2Df> mVelocities;
};

}
