#pragma once

#include "Base_Unit.h"

class Friendly:
	public BaseUnit {

protected:
	float HPRegen, MPRegen, MP, ShieldHP, attackUp, defenseUp;
	int unitCost, unitLevel;

public:
	Friendly(GameDataRef data): BaseUnit(data) {}

	void setUnit(float hp, float mp, float hregen, float mregen, float atk, float def, float shp, int block, float range, float doT, int lane, int cost, float as) {
		
		BaseUnit::setUnit(hp, atk, def, block, range, doT, lane, as);
		
		MP *= mp;
		HPRegen *= hregen;
		MPRegen *= mregen;
		ShieldHP *= shp;
		unitCost = cost;
		unitLevel = 1;
	}

	void takeDamage(float damage) override {

		ostate = HITFLASH;

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
	}

	void setShieldHP(float value) {
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

	void levelUp() {
		if (unitLevel == 5) {
			//Select Upgrades
		}
	}

	void updateDoT(float value) {
		dot += dot * value;
	}

	void updateAttackSpeed(float value) {
		attackSpeed += value;
	}

	bool manaCost(float cost) {
		if (MP - cost >= 0) {
			MP -= cost;
			return true;
		}
		return false;
	}
};