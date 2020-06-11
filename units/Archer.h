#pragma once

#include "Base_Unit.h"
#include "../Game.h"
#include "../Animator.h"

class Archer :
	public BaseUnit
{
private:
	Animator animator;

	sf::Vector2f position;

	LUCY::GameDataRef gdr;

	sf::Sprite charSprite;

public:
	Archer(LUCY::GameDataRef gdr) :gdr(gdr) {position = { 100, 100 }; }

	void setup(sf::Vector2f position) {

		BaseUnit::setUnit(0.75, 0.25, 3, 2, 0, 1, 0.75, 0, 1); //Sets unit info

		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			gdr->assets.GetTexturePtr("Archer_Black"),	//Need a file name
			sf::IntRect(0, 52 * 2, 86, 52),	//Probably stays the same as the golden knight
			sf::Vector2i(86,0), 0.2, 2, true, true
		);

		animator.addAnimationState(
			"Move",
			gdr->assets.GetTexturePtr("Archer_Black"),
			sf::IntRect(0,52*1,86,52),
			sf::Vector2i(86,0), 0.2,3,false,false
		);

		animator.addAnimationState(
			"Attack",
			gdr->assets.GetTexturePtr("Archer_Black"),
			sf::IntRect(0, 52 * 0, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		//Skills

		animator.addAnimationState(
			"PowerShot",
			gdr->assets.GetTexturePtr("Archer_Black"),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState(
			"RhoAias",
			gdr->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 4, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		animator.addAnimationState( //Help me on this skill, create sum random bullshits skill than can win the game but will also cost a lot of shits :/
			"nameTBD",
			gdr->assets.GetTexturePtr(""),
			sf::IntRect(0, 52 * 3, 86, 52),
			sf::Vector2i(86, 0), 0.2, 2, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(position);
		animator.playAnimation("idle");
	}

	void update() {
		BaseUnit::Update();
		animator.updateAnimation();
	}

	void draw(sf::RenderTarget &target) {
		target.draw(charSprite);
	}

	void attack() {
		animator.playAnimation("Attack");
	}

	void run() {
		animator.playAnimation("Move");
	}

	void PowerShot() {
		animator.playAnimation("PowerShot");
	}

	void RhoAias() {
		animator.playAnimation("RhoAias");
	}

	void Ultimate() {
		animator.playAnimation("nameTBD");
	}
};

