#include "Animator.h"

Animator::~Animator()
{
	for (auto it = states.begin(); it != states.end();) {
		delete it->second;
		it = states.erase(it);
	}
	states.clear();
}

void Animator::addAnimationState(std::string key, sf::Texture * texture, sf::IntRect start, sf::Vector2i dim, float delta, int frameCount, bool isLooping, bool isDefault, bool allowCancel)
{
	if (states.find(key) == states.end()) {

		AnimState* as = new AnimState
		(texture, start, delta, frameCount, isLooping);

		spriteDimension = dim;

		states[key] = as;
	}
	else {
		printf("Found same key name in Animator states\n");
	}

	if (isDefault) {
		defaultState = states[key];
	}
}

void Animator::playAnimation(std::string key)
{
	if (states.find(key) == states.end()) {
		printf("Key not found in states!\n");
		return;
	}

	current = states[key];
	current->resetState();

	sprite->setTexture(*current->getTexture());
	sprite->setTextureRect(current->getTexRect());
}

void Animator::updateAnimation()
{
	if (timer.getElapsedTime().asSeconds() < current->getDelta()) {
		return;
	}
	
	timer.restart();

	if (current == nullptr) {
		current = defaultState;
	}

	if (current->getCounter() >= current->getFrameCount()) 
	{
		if (!current->getIsLooping())
		{
			current = defaultState;
		}
		current->resetState();
	}
	else 
	{
		current->advanceToNextFrame(spriteDimension);
	}
	sprite->setTextureRect(current->getTexRect());
}

void Animator::bindSprite(sf::Sprite * sprite)
{
	this->sprite = sprite;
}

void Animator::unbindSprite()
{
	this->sprite = nullptr;
}

// Animstate methods
Animator::AnimState::AnimState(sf::Texture * texture, sf::IntRect start, float delta, int frameCount, bool isLooping, bool allowCancel)
	: texture(texture), start(start), isLooping(isLooping), delta(delta), frameCount(frameCount), allowCancel(allowCancel) {
	current = start;
}

void Animator::AnimState::advanceToNextFrame(sf::Vector2i &dim)
{
	if (counter == frameCount - 1) isDone = true;
	else isDone = false;

	current.left += dim.x;
	current.top += dim.y;

	counter++;
}

void Animator::AnimState::resetState()
{
	current = start;
	counter = 0;
}
