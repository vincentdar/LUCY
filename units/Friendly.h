#pragma once

#include "Base_Unit.h"

class Lane;

namespace UNITS {
	class Friendly :
		public Base 
	{

	protected:
		int unitCost, unitLevel = 1;

	public:
		Friendly(GameDataRef data, Lane* lane, int laneNumber) : Base(data, lane, laneNumber) {}

		void setCost(int cost) { this->unitCost = cost; }
		int getCost() { return unitCost; }

		void setLevel(int level) { this->unitLevel = level; }
		int getLevel() { return unitLevel; }

		void incrementLevel() { this->unitLevel++; }

		void triggerStateChanges() override;
		void updateStateActions() override;

		void setup(sf::Vector2f spawnPosition) override {
			stats.max_health = stats.health;

			base.setSize(sf::Vector2f(100, 10));
			base.setFillColor(sf::Color::White);
			bar.setSize(sf::Vector2f(100, 10));
			bar.setFillColor(sf::Color::Green);
		}
	}; 
}