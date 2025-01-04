#pragma once
#include<SFML/Graphics.hpp>

#include"framework/core.h"


namespace ly
{
	class AssetsManager 
     {
	 public:
		 static AssetsManager& Get();
		 shared<sf::Texture> LoadTexture(const std::string& Path);
		 void CleanCycle();
		 void setAssetsRootDirectory(const std::string& directory);

	 protected:
		 AssetsManager();

	 private:
		 static unique<AssetsManager> assetsManager;
		 Dictionary<std::string, shared<sf::Texture>> mLoadedTextureMap;
		 std::string mRootDirectory;
     };

}