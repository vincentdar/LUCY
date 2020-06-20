#pragma once

#include "Spearman.h"

class WanderingLancer : public Spearman {
public:
	WanderingLancer(GameDataRef data): Spearman(data){}

	void setup(sf::Vector2f position) {
		//1.25, 0.3, 3, 5, 1.5, 0.5, 0, 2, 6.5f, 0, -1, 12, 8.0f
		Friendly::setUnit(2, 1, 7, 7, 3, 2, 0, 3, 8.0f, 0, -1, 16, 9.5f);

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
			"ManaBurst",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState(
			"Gungnir",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false);

		animator.addAnimationState(
			"DivineThrust",
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
		animator.playAnimation("ManaBurst");
		ostate = SKILL1;
		if(manaCost(30) == true){
			updateAttack(5);
			updateAttackSpeed(20);
		}
		//For 10s, CD = 30s
	}

	void Skill2() override {
		animator.playAnimation("Gungnir");
		ostate = SKILL2;
		Spearman::Skill2();
	}

	void Ultimate() override {
		animator.playAnimation("DivineThrust");
		ostate = SKILL4;
		if (manaCost(100) == true)
			updateAttackSpeed(25);
		//For 20s, CD = 40s
	}
};