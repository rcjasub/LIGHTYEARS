
#include "AssetManager.hpp"

namespace ly
{
    unique<AssetManager> AssetManager::smAssetManager{nullptr};

    AssetManager::AssetManager(): mAssetRootDirectory{}
    {

    }

    AssetManager& AssetManager::Get()
    {
        if(!smAssetManager)
        {
            // smAssetManager = std::move(std::make_unique<AssetManager>());
            smAssetManager = unique<AssetManager>{new AssetManager()};
        }
        return *smAssetManager;
    }

    shared<sf::Texture> AssetManager::LoadTexture(const std::string &path)
    {
        return LoadAsset(path, mLoadedTextureMap);
    }

    shared<sf::Font> AssetManager::LoadFont(const std::string &path)
    {
        return LoadAsset(path, mLoadedFontMap);
    }

    void AssetManager::CleanCycle()
    {
        CleanUniqueRef(mLoadedFontMap);
        CleanUniqueRef(mLoadedTextureMap);
    }

    void AssetManager::SetAssetRootDirectory(const std::string &directory)
    {
        mAssetRootDirectory = directory;
    }

    template<typename T>
    shared<T> AssetManager::LoadAsset(const std::string &path, Dictionary<std::string, shared<T>> &container)
    {
        const auto found = container.find(path);
        if(found != container.end())
        {
            return found->second;
        }

        shared<T> newItem{new T};
        if(newItem->loadFromFile(mAssetRootDirectory + path))
        {
            container[path] = newItem;
            return newItem;
        }

        LOG("Item Not Found : %s", (mAssetRootDirectory + path).c_str());
        return shared<T>{nullptr};
    }

    template<typename T>
    void AssetManager::CleanUniqueRef(Dictionary<std::string, shared<T>> &container)
    {
        for(auto iter = container.begin(); iter != container.end();)
        {
            if(iter->second.unique())
            {
                LOG("Cleaning texture: %s", iter->first.c_str());
                iter = container.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}
