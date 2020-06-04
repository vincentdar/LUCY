#include "AssetManager.h"

namespace LUCY
{
	void AssetManager::LoadTexture(std::string name, std::string fileName)
	{
		sf::Texture tex;
		if (tex.loadFromFile(fileName))
		{
			m_textures[name] = tex;
		}
	}

	sf::Texture& AssetManager::GetTexture(std::string name)
	{
		return m_textures.at(name);
	}

	void AssetManager::LoadFonts(std::string name, std::string fileName)
	{
		sf::Font font;
		if (font.loadFromFile(fileName))
		{
			m_fonts[name] = font;
		}
	}

	sf::Font& AssetManager::GetFont(std::string name)
	{
		return m_fonts.at(name);
	}

	void AssetManager::LoadSoundBuffer(std::string name, std::string fileName)
	{
		sf::SoundBuffer sb;
		if (sb.loadFromFile(fileName))
		{
			m_soundBuffers[name] = sb;
		}
	}

	sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string name)
	{
		return m_soundBuffers.at(name);
	}

}
