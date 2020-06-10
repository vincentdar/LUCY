#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>

#include <iostream>
#include <sstream>
#include <fstream>
#include "Macro.h"
#include "Utils.h"
#include <assert.h>

namespace LUCY
{
	class AssetManager
	{
	private:
		std::map<std::string, sf::Texture> m_textures;
		std::map<std::string, sf::Font> m_fonts;
		std::map<std::string, sf::SoundBuffer> m_soundBuffers;
		std::map<std::string, std::string> m_musicPaths;
	public:
		void LoadTexture(const std::string& name, const std::string& fileName);
		sf::Texture& GetTexture(const std::string& name);

		// Tambahan
		sf::Texture* GetTexturePtr(const std::string& name);

		void LoadFonts(const std::string& name, const std::string& fileName);
		sf::Font& GetFont(const std::string& name);

		void AddMusicPath(const std::string& name, const std::string& path);
		const std::string& GetMusicPath(const std::string& name);

		void LoadSoundBuffer(const std::string& name, const std::string& fileName);
		sf::SoundBuffer& GetSoundBuffer(const std::string& name);

		sf::SoundBuffer* GetSoundBufferPtr(const std::string& name);

		void LoadAssetFromText(const std::string& filename);
	};
}

