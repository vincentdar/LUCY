#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class Animator
{
private:
	class AnimState
	{
	private:
		// Tex pointer yg disimpan (pointer)
		sf::Texture* texture;

		// Posisi awal
		sf::IntRect start;

		// Size (dimensi)
		sf::IntRect current;

		float delta;
		bool isLooping;
		int frameCount;

		int counter = 0;

	public:
		AnimState(sf::Texture* texture, sf::IntRect start, 
			float delta, bool isLooping, int frameCount);

		void advanceToNextFrame(sf::Vector2i &dim);
		void resetState();
		
		float getDelta() { return delta; }
		bool getIsLooping() { return isLooping; }
		int getFrameCount() { return frameCount; }
		int getCounter() { return counter; }

		sf::IntRect& getTexRect() { return current; }

		sf::Texture* getTexture() { return texture; }
	};

	sf::Clock timer;

	sf::Vector2i spriteDimension;

	sf::Sprite* sprite;
	AnimState* current;

	AnimState* defaultState;
	
	std::unordered_map<std::string, AnimState*> states;

public:
	~Animator();

	void addAnimationState(std::string key, sf::Texture* texture, sf::IntRect start, sf::Vector2i dim, float delta, int frameCount, bool isLooping, bool isDefault = false);

	void playAnimation(std::string key);
	void updateAnimation();

	void bindSprite(sf::Sprite* sprite);

	void unbindSprite();
};
