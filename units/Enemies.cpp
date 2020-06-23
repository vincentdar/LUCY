#include "Enemies.h"

#include "../Lane.h"

namespace UNITS
{
	void Enemies::triggerStateChanges() {
		if (state != ATTACK) {
			// If enemy is close, setState attack
			// SAMPLE MELEE ATTACK!1!1
			int friendlyWithMinDistance = INT_MAX;
			Friendly* friendlyUnit = nullptr;
			for (int i = 0; i < laneDataRef[laneNumber].getFriendlyCount(); i++)
			{
				int distance = charSprite.getPosition().x - laneDataRef[laneNumber].getFriendlyUnit(i)->getPosition().x;
				if (distance < stats.range && distance < friendlyWithMinDistance && distance > 0)
				{
					friendlyWithMinDistance = distance;
					friendlyUnit = laneDataRef[laneNumber].getFriendlyUnit(i);
				}
			}

			if (friendlyUnit != nullptr) {
				this->setState(ATTACK);
				friendlyUnit->takeDamage(stats.normalDamage);
				friendlyUnit = nullptr;
				clock.restart();
			}
		}
	}

	void Enemies::updateStateActions()
	{
		if (state == ATTACK) {
			if (clock.getElapsedTime().asSeconds() >= 2.0) {
				this->setState(MOVE);
				clock.restart();
				interval.restart();
			}
		}
		else if (state == MOVE) {
			if (isAttacking) {
				if (interval.getElapsedTime().asSeconds() >= 2.0) {
					setState(ATTACK);
					interval.restart();
				}
			}
		}
	}
}