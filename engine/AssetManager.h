#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>

#include <iostream>
#include <sstream>
#include <fstream>
#include "../engine/Macro.h"
#include "../utils/Utils.h"

namespace LUCY
{
	class AssetManager
	{
	private:
		std::map<std::string, sf::Texture> m_textures;
		std::map<std::string, sf::Font> m_fonts;
		std::map<std::string, sf::SoundBuffer> m_soundBuffers;
	public:
		void LoadTexture(std::string name, std::string fileName);
		sf::Texture& GetTexture(std::string name);

		void LoadFonts(std::string name, std::string fileName);
		sf::Font& GetFont(std::string name);

		void LoadSoundBuffer(std::string name, std::string fileName);
		sf::SoundBuffer& GetSoundBuffer(std::string name);

		void LoadAssetFromText(std::string filename);
	};
}

