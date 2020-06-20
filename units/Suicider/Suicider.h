#pragma once

#include "../Friendly.h"

class Suicider :
	public Friendly
{
public:
	Suicider(LUCY::GameDataRef data) :Friendly(data) { }

	void setup(sf::Vector2f position) {

		Friendly::setUnit(0.1, 0, 0, 0, 7, 0, 0, 0, 0, 0, -1, 5, 0); //Sets unit info

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr(""),	//Need a file name
			sf::IntRect(0, 52 * 2, 86, 52),	//Probably stays the same as the golden knight
			sf::Vector2i(86, 0), 0.2, 2, true, true
		);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 1, 86, 52),
			sf::Vector2i(86, 0), 0.2, 3, false, false
		);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 0, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		//Skills

		animator.addAnimationState(
			"Suicide",
			data->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("Idle");
	}

	void update() {
		BaseUnit::update();
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
		animator.playAnimation("Suicide");
		ostate = SKILL4;
		//After cast / While casting isAlive = false;
	}
};


