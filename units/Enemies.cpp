#include "Enemies.h"

#include "../Lane.h"
#include "../projectiles/Arrow.h"

namespace UNITS
{
	void Enemies::triggerStateChanges() {
		if (state != ATTACK) {

			bool targetIsInRange = false;
			for (int i = 0; i < laneDataRef[laneNumber].getFriendlyCount(); i++)
			{
				int distance = charSprite.getPosition().x - laneDataRef[laneNumber].getFriendlyUnit(i)->getPosition().x;
				if (distance < stats.range && distance > 0)
				{
					targetIsInRange = true;
				}
			}

			if (targetIsInRange) {
				this->setState(ATTACK);
				clock.restart();
			}
		}
	}

	void Enemies::updateStateActions()
	{
		if (state == ATTACK) {
			if (clock.getElapsedTime().asSeconds() >= 1.5) {
				//laneDataRef[laneNumber].spawnEnemyProjectile(new UNITS::Arrow());
				this->setState(MOVE);
				clock.restart();
			}
		}
	}
}