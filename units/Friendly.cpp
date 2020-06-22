#include "Friendly.h"

#include "../Lane.h"

namespace UNITS
{
	void Friendly::triggerStateChanges() {
		if (state != ATTACK) {
			// If enemy is close, setState attack
			// SAMPLE MELEE ATTACK!1!1
			int enemyWithMinDistance = INT_MAX;
			Enemies* enemyUnit = nullptr;
			for (int i = 0; i < laneDataRef[laneNumber].getEnemyCount(); i++)
			{
				int distance = laneDataRef[laneNumber].getEnemyUnit(i)->getPosition().x - charSprite.getPosition().x;
				if (distance < stats.attackRange && distance < enemyWithMinDistance && distance > 0)
				{
					enemyWithMinDistance = distance;
					enemyUnit = laneDataRef[laneNumber].getEnemyUnit(i);
				}
			}

			if (enemyUnit != nullptr) {
				this->setState(ATTACK);
				enemyUnit->takeDamage(stats.attack);
				enemyUnit = nullptr;
				clock.restart();
			}
		}
	}

	void Friendly::updateStateActions()
	{
		if (state == ATTACK) {
			if (clock.getElapsedTime().asSeconds() >= 2.0) {
				this->setState(IDLE);
				clock.restart();
			}
		}
	}
}