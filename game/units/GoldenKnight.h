#pragma once

#include "Base_Unit.h"
#include "../../engine/Game.h"
#include "../../engine/animation/Animator.h"

class GoldenKnight 
	: public BaseUnit
{
private:
	Animator animator;

	sf::Vector2f position;

	LUCY::GameDataRef gdr;

	sf::Sprite charSprite;

public:
	GoldenKnight(LUCY::GameDataRef gdr) : gdr(gdr) { }

	void setup(sf::Vector2f position) {

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle", 
			gdr->assets.GetTexturePtr("Knight_Gold"), 
			sf::IntRect(0, 52 * 2, 86, 52), 
			sf::Vector2i(86, 0), 0.2, 2, true, true);

		animator.addAnimationState(
			"Move", 
			gdr->assets.GetTexturePtr("Knight_Gold"), 
			sf::IntRect(0, 52 * 1, 86, 52), 
			sf::Vector2i(86, 0), 0.2, 3, false, false);

		animator.addAnimationState(
			"Attack", 
			gdr->assets.GetTexturePtr("Knight_Gold"), 
			sf::IntRect(0, 52 * 0, 86, 52), 
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState("Bash",
			gdr->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle"); 

	}

	void update() {
		animator.updateAnimation();
	}

	void draw(sf::RenderTarget& target) {
		target.draw(charSprite);
	}

	void attack() {
		animator.playAnimation("Attack");
	}

	void run() {
		animator.playAnimation("Move");
	}

	void bash() {
		animator.playAnimation("Bash");
	}
};