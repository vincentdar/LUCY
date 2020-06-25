#pragma once

#include "Base_Unit.h"

class Lane;

namespace UNITS {
	class Friendly :
		public Base 
	{

	protected:
		static int unitCost;

	public:
		Friendly(GameDataRef data, Lane* lane, int laneNumber) : Base(data, lane, laneNumber) {}

		static int getCost() { return unitCost; }

		void triggerStateChanges() override;
		void updateStateActions() override;

		void setup(sf::Vector2f spawnPosition) override {
			stats.max_health = stats.health;

			base.setSize(sf::Vector2f(100, 10));
			base.setFillColor(sf::Color::White);
			bar.setSize(sf::Vector2f(100, 10));
			bar.setFillColor(sf::Color::Green);
		}

		virtual std::string getType() = 0;

		
	};
}