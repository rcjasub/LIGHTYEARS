
#pragma once

#include "Core.hpp"
#include <SFML/Graphics.hpp>

namespace ly
{
    class AssetManager
    {
    public:
        ~AssetManager() = default;
        static AssetManager& Get();
        shared<sf::Texture> LoadTexture(const std::string& path);
        shared<sf::Font> LoadFont(const std::string & path);
        void CleanCycle();
        void SetAssetRootDirectory(const std::string& directory);
    protected:
        AssetManager();

    private:
        template<typename T>
        shared<T> LoadAsset(const std::string& path, Dictionary<std::string, shared<T>>& container);
        template<typename T>
        void CleanUniqueRef(Dictionary<std::string, shared<T>>& container);
        static unique<AssetManager> smAssetManager;
        Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
        Dictionary<std::string, shared<sf::Font>> mLoadedFontMap;
        std::string mAssetRootDirectory;
    };
}


