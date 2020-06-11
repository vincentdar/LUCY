#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <queue>

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

		// Frame counter
		float delta;
		int frameCount;
		int counter = 0;

		// Booleans
		bool isLooping;
		bool allowCancel;
		bool isDone;

	public:
		AnimState(sf::Texture* texture, sf::IntRect start, 
			float delta, int frameCount, bool isLooping, bool allowCancel = false);

		void advanceToNextFrame(sf::Vector2i &dim);
		void resetState();
		
		float getDelta() { return delta; }
		bool getIsLooping() { return isLooping; }
		int getFrameCount() { return frameCount; }
		int getCounter() { return counter; }

		sf::IntRect& getTexRect() { return current; }

		sf::Texture* getTexture() { return texture; }

		bool getAllowCancel() { return allowCancel; }
	};

	sf::Clock timer;

	sf::Vector2i spriteDimension;

	sf::Sprite* sprite;

	AnimState* current;

	AnimState* defaultState;
	
	std::unordered_map<std::string, AnimState*> states;

	std::queue<AnimState*> queueStates;

public:
	~Animator();

	void addAnimationState(std::string key, sf::Texture* texture, sf::IntRect start, sf::Vector2i dim, float delta, int frameCount, bool isLooping, bool isDefault = false, bool allowCancel = false);

	void playAnimation(std::string key);
	void updateAnimation();

	void bindSprite(sf::Sprite* sprite);

	void unbindSprite();
};
