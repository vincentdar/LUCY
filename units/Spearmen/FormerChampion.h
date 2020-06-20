#pragma once

#include "Spearman.h"

class FormerChampion : public Spearman {
public:
	FormerChampion(GameDataRef data): Spearman(data){}

	void setup(sf::Vector2f position) {
		
		Friendly::setUnit(4, 2.5, 10, 7, 4, 4, 250, 5, 5.0f, 0, -1, 16, 10.0f);

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
			"DivineThrust",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState(
			"Gungnir4",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState(
			"GaeBolg",
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
		animator.playAnimation("DivineThrust");
		ostate = SKILL1;
		if (manaCost(100) == true)
			updateAttackSpeed(30);
		//For 20s, CD = 40s
	}

	void Skill2() override {
		animator.playAnimation("Gungnir4");
		ostate = SKILL2;
		if (manaCost(120) == true)
			updateAttack(10);
		//For 1 attack, CD = 15s
	}

	void Ultimate() override {
		animator.playAnimation("GaeBolg");
		ostate = SKILL4;
		if (manaCost(175) == true)
			updateAttack(200);
		//For 1 hit only, CD = 100s
	}
};