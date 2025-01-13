#pragma once
#include <SFML/Graphics.hpp>

#include"framework/core.hpp"

namespace ly
{
	class AssetsManager
	{
	public:
		static AssetsManager& Get();
		shared<sf::Texture> LoadTexture(const std::string& Path);
		shared<sf::Font> LoadFont(const std::string& Path);
		void CleanCycle();
		void setAssetsRootDirectory(const std::string& directory);

	protected:
		AssetsManager();

	private:
		template<typename T>
		shared<T> LoadAssets(const std::string& Path, Dictionary<std::string, shared<T>>& container);

		static unique<AssetsManager> assetsManager;
		Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
		Dictionary<std::string, shared<sf::Font>> mLoadedFontMap;
		std::string mRootDirectory;

		template<typename T>
		void CleanUniqueRef(Dictionary<std::string, shared<T>>& container);

	};

	template<typename T>
	inline shared<T> AssetsManager::LoadAssets(const std::string& Path, Dictionary<std::string, shared<T>>& container)
	{
		auto found = container.find(Path);
		if (found != container.end())
		{
			return found->second;
		}

		shared<T> newAssets{ new T };
		if (newAssets->loadFromFile(mRootDirectory + Path))
		{
			container.insert({ Path, newAssets });
			return newAssets;
		}

		return shared<T> {nullptr};
	}

	template<typename T>
	inline void AssetsManager::CleanUniqueRef(Dictionary<std::string, shared<T>>& container)
	{
		for (auto iter = container.begin(); iter != container.end();)
		{
			if (iter->second.unique())
			{
				LOG("Cleaning: %s", iter->first.c_str());
				iter = container.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

}