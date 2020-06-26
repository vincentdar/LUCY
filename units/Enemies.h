#pragma once

#include "Base_Unit.h"
#include "Wall.h"

namespace UNITS
{
	class Enemies : public Base 
	{
	protected:
		bool isAttacking;

		sf::Clock interval;
		sf::Clock gracePeriod;
		sf::Clock skillTimer;

		float attackUp;
		int numOfAttacks;

		// Reference ke wall yang ada di gamestate
		Wall* wall;

	public:
		Enemies(GameDataRef data, Lane* lane, int laneNumber, Wall* wall) 
			: Base(data, lane, laneNumber), wall(wall) {
			interval.restart();
			gracePeriod.restart();
			skillTimer.restart();
			isAttacking = false;
		}

		virtual void triggerStateChanges() override;
		virtual void updateStateActions() override;
		void update() override;

		void setup(sf::Vector2f spawnPosition) override {
			stats.max_health = stats.health;

			base.setSize(sf::Vector2f(100, 10));
			base.setFillColor(sf::Color::White);
			bar.setSize(sf::Vector2f(100, 10));
			bar.setFillColor(sf::Color::Red);
		}
	};
}

