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
		auto found = mLoadedTextureMap.find(Path);
		if (found != mLoadedTextureMap.end())
		{
			return found->second;
		}

		shared<sf::Texture> newTexture{ new sf::Texture };
		if (newTexture->loadFromFile(mRootDirectory + Path))
		{
			mLoadedTextureMap.insert({ Path, newTexture });
			return newTexture;
		}

		return shared<sf::Texture> {nullptr};
	}

	void AssetsManager::CleanCycle()
	{
		for (auto iter = mLoadedTextureMap.begin(); iter != mLoadedTextureMap.end();)
		{
			if (iter->second.unique())
			{
				iter = mLoadedTextureMap.erase(iter);
			}

			else
			{
				++iter;
			}
		}
	}

	void AssetsManager::setAssetsRootDirectory(const std::string& directory)
	{
		mRootDirectory = directory;
	}

	AssetsManager::AssetsManager() : mRootDirectory {}
	{

	}
}