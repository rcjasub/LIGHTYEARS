#include "framework/AssetsManager.hpp"
#include "framework/core.hpp"

namespace ly
{
    unique<AssetsManager> AssetsManager::assetsManager{nullptr};

    AssetsManager& AssetsManager::Get()
    {
        if (!assetsManager)
        {
            assetsManager = unique<AssetsManager>{new AssetsManager};
        }

        return *assetsManager;
    }

    shared<sf::Texture> AssetsManager::LoadTexture(const std::string& Path)
    {
        return LoadAssets(Path, mLoadedTextureMap);
    }

    shared<sf::Font> AssetsManager::LoadFont(const std::string& Path)
    {
        return LoadAssets(Path, mLoadedFontMap);
    }

    void AssetsManager::CleanCycle()
    {
        CleanUniqueRef(mLoadedFontMap);
        CleanUniqueRef(mLoadedTextureMap);
    }

    void AssetsManager::setAssetsRootDirectory(const std::string& directory)
    {
        mRootDirectory = directory;
    }

    AssetsManager::AssetsManager() : mRootDirectory {}
    {

    }
}