#pragma once

#include <SFML/Graphics.hpp>

#include "Base_Unit.h"
#include "../Game.h"
#include "../Animator.h"

struct Position
{
	int x;
	int y;
};

class BaseUnit
{
protected:
	float HP, MP, HPRegen, MPRegen, MovementSpeed, Attack, Defend, ShieldHP, attackUp, defenseUp;
	int Blocks;
	bool isAlive, isHit;
	int id;
	Position pos;

	sf::Sprite charSprite;

public:
	BaseUnit() : HP(100), MP(75), HPRegen(1), MPRegen(1), MovementSpeed(1), Attack(75), Defend(50), ShieldHP(0), Blocks(1), isAlive(true), isHit(false), attackUp(0), defenseUp(0) {}

	void setUnit(float hp, float mp, float hregen, float mregen, float ms, float atk, float def, float shp, int block) {
		HP *= hp;
		MP *= mp;
		HPRegen *= hregen;
		MPRegen *= mregen;
		MovementSpeed *= ms;
		Attack *= atk;
		Defend *= def;
		ShieldHP *= shp;
		Blocks *= block;
	}

	virtual void setup(sf::Vector2f position) = 0;
	virtual void update() = 0;

	virtual void draw(sf::RenderTarget& target) {
		target.draw(charSprite);
	}

	virtual void draw(sf::RenderTarget& target, sf::Shader* shader) {
		target.draw(charSprite, shader);
	}

	virtual void attack() = 0;
	virtual void run() = 0;
	
	virtual void idle() {}
	virtual void die() {}
	virtual void doSkill() {}

	Position GetPosition() { return pos; }

	void takeDamage(float damage) {
		if (ShieldHP > 0) {

			ShieldHP -= damage;

			if (ShieldHP < 0) {
				HP += (ShieldHP - Defend - defenseUp);
				ShieldHP = 0;
			}
		}
		else
			HP -= (damage - Defend - defenseUp);

		if (HP <= 0)
			isAlive = false;

		//i still have no idea on what to do with isHit var, initially
		//initially i wanted to make it that if the unit gets hit, then isHit is set
		//to true, and then after some deltaTime then the isHit is set to false
		//this will allow the unit to do / play / activate some of the passive ability
		//the unit have
	}

	void getShieldHP(float value) {
		ShieldHP += value;
	}

	void regenEverything() {
		HP += HPRegen;
		MP += MPRegen;
	}

	void updateHPRegen(float value) {
		HPRegen += value;
	}

	void updateMPRegen(float value) {
		MPRegen += value;
	}

	void updateAttack(float value) {
		attackUp = Attack * value; //Value is the % of dmg, EG value = 0.5 which means 50%Attack
	}

	void updateDefend(float value) {
		defenseUp = Defend * value; //This will help to reset to the original value
	}

	void blockEnemy() { //this function is supposed to count how many enemy this / the unit is currently holding, if it exceds, then the new enemy will pass thru, i think a vector is needed (?)

	}
};
