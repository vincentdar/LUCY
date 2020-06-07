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

	sf::Texture * AssetManager::GetTexturePtr(std::string name)
	{
		return &m_textures[name];
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

	void AssetManager::LoadAssetFromText(std::string filename)
	{
		std::ifstream inStream;
		inStream.open(ASSET_CONF);

		if (!inStream.is_open()) {
			std::cout << "FAILED TO OPEN FILE\n";
			return;
		}

		enum State {
			NONE, TEXTURES, SOUNDS, FONTS
		};

		State state = NONE;
		std::string line;
		int line_counter = 1;
		while (std::getline(inStream, line)) {

			// Clear whitespace didpn
			UTILS.clearSpacesInFront(line);

			// Check if it is a comment.
			if (line[0] == '#') {
				continue;
			}
			else {
				int i_letter = 0;
				std::string assetName;
				std::string pathName;

				while (i_letter < line.length()) {

					if (line[i_letter] == ':') {
						 assetName = line.substr(0, i_letter);
						 pathName = line.substr(i_letter + 1, line.length() - i_letter);
						 break;
					}
					i_letter++;
				}

				// Check tipe apa dia.
				UTILS.clearSpacesInFront(pathName);

				if (pathName.length() == 0) {
					// Its a typename!
					std::string asset = UTILS.getLowercase(assetName);
					if (asset == "texture") {
						state = TEXTURES;
					}
					else if (asset == "fonts") {
						state = FONTS;
					}
					else if (asset == "sounds") {
						state = SOUNDS;
					}
				}
				else {
					switch (state)
					{
					case NONE:
						std::cout << "ERROR! Undefined type on line: " << line_counter << std::endl;
						break;
					case TEXTURES:
						LoadTexture(assetName, pathName);
						break;
					case SOUNDS:
						LoadSoundBuffer(assetName, pathName);
						break;
					case FONTS:
						LoadFonts(assetName, pathName);
						break;
					default:
						break;
					}
				}
				line_counter++;
			}
		}
	}

}
