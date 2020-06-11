#pragma once

#include "Base_Unit.h"
#include "../Game.h"
#include "../Animator.h"

class GoldenKnight
	: public BaseUnit
{
private:
	Animator animator;

	sf::Vector2f position;

	LUCY::GameDataRef gdr;

	sf::Sprite charSprite;

public:
	GoldenKnight(LUCY::GameDataRef gdr) : gdr(gdr) { position = { 100, 100 }; }

	void setup(sf::Vector2f position) {

		BaseUnit::setUnit(1.25, 0.3, 3, 5, 0, 1.5, 0.5, 0, 2);

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
			sf::Vector2i(86, 0), 0.2, 3, true, false);

		animator.addAnimationState(
			"Attack",
			gdr->assets.GetTexturePtr("Knight_Gold"),
			sf::IntRect(0, 52 * 0, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		//Skills

		animator.addAnimationState("Gungnir",
			gdr->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState("GaeBolg",
			gdr->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);
		//Skill mungkin bisa tak ubah kalo tidak ada spritenya, tak buat maneh sing sesuai mbek sprite sing ada

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");

	}

	void update() {
		BaseUnit::Update();
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

	void Gungnir() {
		animator.playAnimation("Gungnir");

	}

	void Ultimate() {
		animator.playAnimation("GaeBolg");
	}
};