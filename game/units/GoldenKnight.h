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
	sf::Texture idleTexture;

public:
	GoldenKnight(LUCY::GameDataRef gdr) : gdr(gdr) { position = { 100, 100 }; }

	void setup() {

		charSprite.setPosition(position);

		animator.bindSprite(&charSprite);
		animator.addAnimationState("Idle", gdr->assets.GetTexturePtr("Knight_G_Idle"), sf::IntRect(0, 0, 32, 41), sf::Vector2i(32, 0), 0.3, 2, true, true);

		charSprite.setScale(2, 2);
		charSprite.setPosition(100, 100);
		animator.playAnimation("Idle");
	}

	void update() {
		animator.updateAnimation();
	}

	void draw(sf::RenderTarget& target) {
		target.draw(charSprite);
	}
};