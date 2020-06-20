#pragma once

#include "../Friendly.h"

class Spearman
	: public Friendly
{
public:
	Spearman(LUCY::GameDataRef data) : Friendly(data) { }
	void setup(sf::Vector2f position) {

		Friendly::setUnit(1.25, 0.3, 3, 5, 1.5, 0.5, 0, 2, 6.5f, 0, -1, 12, 8.0f);

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 2, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, true, true);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 1, 86, 52),
			sf::Vector2i(86, 0), 0.2, 3, false, false);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 0, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		//Skills
		animator.addAnimationState(
			"Thrust",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState(
			"Gungnir",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState(
			"HeartSeeker",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 5, 86, 52),
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

	void Skill1() override {
		animator.playAnimation("Thrust");
		ostate = SKILL1;
		if (manaCost(5) == true)
			updateAttack(3);
		//For 1 attack, CD = 5s
	}

	void Skill2() override {
		animator.playAnimation("Gungnir");
		ostate = SKILL2;
		if(manaCost(10) == true)
			updateAttack(5);
		//For 1 attack, CD = 10s
	}

	void Ultimate() override {
		animator.playAnimation("HeartSeeker");
		ostate = SKILL4;
		if (manaCost(50) == true)
			updateAttack(1.45);
		//For 1 attack, CD = 80s
	}
};