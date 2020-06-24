//#pragma once
//
//#include "Friendly.h"
//
//class Defender :
//	public Friendly
//{
//
//public:
//	Defender(GameDataRef data) :Friendly(data) {
//		//Set units info
//		BaseUnit::setHP(3);
//		BaseUnit::setAttack(0);
//		BaseUnit::setCurrentLane(-1);
//		BaseUnit::setDef(5);
//		Friendly::setDoT(0);
//		BaseUnit::setRange(0);
//		Friendly::setMP(0.2);
//		Friendly::setShieldHP(0);
//		Friendly::setUnitCost(15);
//		Friendly::setUnitLevel(1);
//	}
//
//	void setup(sf::Vector2f position) {
//
//		animator.bindSprite(&charSprite);
//
//		//36 x 42
//		animator.addAnimationState(
//			"Idle",
//			data->assets.GetTexturePtr("Defender"),	
//			sf::IntRect(0, 42 * 0, 36, 42),	
//			sf::Vector2i(36, 0), 0.2, 5, true, true
//		);
//
//		animator.addAnimationState(
//			"Move",
//			data->assets.GetTexturePtr(""),
//			sf::IntRect(0, 42 * 1, 36, 42),
//			sf::Vector2i(36, 0), 0.2, 11, false, false
//		);
//
//		//Skills
//
//		charSprite.setScale(2, 2);
//		charSprite.setPosition(position);
//		animator.playAnimation("Idle");
//	}
//
//	void update() {
//		BaseUnit::update();
//		animator.updateAnimation();
//	}
//
//	void draw(sf::RenderTarget& target) {
//		target.draw(charSprite);
//	}
//
//	void attack() {
//		animator.playAnimation("Attack");
//	}
//
//	void run() {
//		animator.playAnimation("Move");
//	}
//};
//
