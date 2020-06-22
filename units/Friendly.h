#pragma once

#include "Base_Unit.h"

class Lane;

namespace UNITS {
	class Friendly :
		public Base 
	{
	protected:
		int unitCost, unitLevel;

	public:
		Friendly(GameDataRef data, Lane* lane, int laneNumber) : Base(data, lane, laneNumber) 
		{
			stats.mp = 100;
			stats.attackUp = 0;
			stats.defenseUp = 0;
			
			stats.shieldHP = 0;

			doT = 0;

			unitCost = 0;
			unitLevel = 1;
		}

		void setCost(int cost) { this->unitCost = cost; }
		int getCost() { return unitCost; }

		void setLevel(int level) { this->unitLevel = level; }
		int getLevel() { return unitLevel; }

		void incrementLevel() { this->unitLevel++; }

		void triggerStateChanges() override;
		void updateStateActions() override;

		// PAMs
		float getMP() { return stats.mp; }
		void setMP(float mp) { stats.mp = mp; }

		float getSheld() { return stats.shieldHP; }
		void setShieldHP(float shield) { stats.shieldHP = shield; }

		float getAttackUp() { return stats.attackUp; }
		void setAttackUp(float up) { stats.attackUp = up; }

		float getDefUP() { return stats.defenseUp; }
		void setDefUp(float up) { stats.defenseUp = up; }

		float getDoT() { return doT; }
		void setDoT(float DoT) { doT = DoT; }

		int getUnitCost() { return unitCost; }
		void setUnitCost(int cost) { unitCost = cost; }

		int getUnitLevel() { return unitLevel; }
		void setUnitLevel(int level) { unitLevel = level; }

		void updateShield(float value) { stats.shieldHP += value; }

		void updateAttack(float value) {
			stats.attackUp = stats.attack * value; //Value is the % of dmg, EG value = 0.5 which means 50%Attack
		}

		void updateDefend(float value) {
			stats.defenseUp = stats.defense * value; //This will help to reset to the original value
		}

		void levelUp() {
			//Use money or exp ?
		}

		void updateDoT(float value) {
			doT += value;
		}

		void updateAttackSpeed(float value) {
			stats.attackSpeed += value;
		}

		bool manaCost(float cost) {
			if (stats.mp - cost >= 0) {
				stats.mp -= cost;
				return true;
			}
			return false;
		}
	};
}