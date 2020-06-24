#include "Friendly.h"

#include "../Lane.h"

namespace UNITS
{
	void Friendly::triggerStateChanges() {
		if (state != ATTACK) {
			// If enemy is close, setState attack
			// SAMPLE MELEE ATTACK!1!1
			int enemyWithMinDistance = INT_MAX;
			for (int i = 0; i < laneDataRef[laneNumber].getEnemyCount(); i++)
			{
				int distance = laneDataRef[laneNumber].getEnemyUnit(i)->getPosition().x - charSprite.getPosition().x;
				if (distance < stats.range && distance < enemyWithMinDistance && distance > 0)
				{
					enemyWithMinDistance = distance;
					targetedEntity = laneDataRef[laneNumber].getEnemyUnit(i);
				}
			}

			if (targetedEntity != nullptr) {
				this->setState(ATTACK);
				targetedEntity->takeDamage(stats.normalDamage);
				targetedEntity = nullptr;
				clock.restart();
			}
		}
	}

	void Friendly::updateStateActions()
	{
		if (state == ATTACK) {
			if (clock.getElapsedTime().asSeconds() >= stats.attackSpeed) {
				this->setState(IDLE);
				clock.restart();
			}
		}
	}
}