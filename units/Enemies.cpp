#include "Enemies.h"

#include "../Lane.h"

namespace UNITS
{
	void Enemies::triggerStateChanges() {
		if (state != ATTACK) {
			// Apabila ketemu musuh in range, play animation
			// ketika animation selesai, baru take damage
			int friendlyWithMinDistance = INT_MAX;
			for (int i = 0; i < laneDataRef[laneNumber].getFriendlyCount(); i++)
			{
				int distance = charSprite.getPosition().x - laneDataRef[laneNumber].getFriendlyUnit(i)->getPosition().x;
				if (distance < stats.range && distance < friendlyWithMinDistance && distance > 0)
				{
					friendlyWithMinDistance = distance;
					targetedEntity = laneDataRef[laneNumber].getFriendlyUnit(i);
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

	void Enemies::updateStateActions()
	{
		if (state == ATTACK) {
			if (clock.getElapsedTime().asSeconds() >= stats.attackSpeed) {
				this->setState(MOVE);
				clock.restart();
			}
		}

		else if (state == MOVE) {
			charSprite.move(-1 * stats.movementSpeed, 0);
		}
	}
	void Enemies::update()
	{
		Base::update();
		
		// Musuh bisa menginjak wheat jadi busuk
		for (int i = 0; i < laneDataRef[laneNumber].getWheatCount(); i++)
		{
			LUCY::Wheat* wh = laneDataRef[laneNumber].getWheat(i);
			if (wh->getSprite().getGlobalBounds().intersects(charSprite.getGlobalBounds()))
			{
				wh->Pillaged();
			}
		}

		
	}
}