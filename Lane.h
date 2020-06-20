#pragma once

#include <SFML/Graphics.hpp>

#include "units/Base_Unit.h"
#include "projectiles/Projectiles.h"

#include <vector>

class Lane
{
private:
	// Lane menyimpan semua unit yg ada 
	// Enemies
	std::vector<BaseUnit*>	enemy_units;

	// Friendlies
	std::vector<BaseUnit*>	friendly_units;

	// Projectiles
	std::vector<Projectile*> projectiles;

	// Setiap unit hanya menyimpan value x : y nya tetap sama (1 baseline tiap lane)
	//  jadi nilai y dari vector2f ini dipakai utk spawn unit friendly dan enemy
	sf::Vector2f			enemyLaneSpawnPoint;

	sf::FloatRect			lane_dimension;

	sf::Texture*			lane_texture;
	sf::RectangleShape		lane_rect;

public:
	Lane() {}
	~Lane() {
		for (int i = 0; i < friendly_units.size(); i++) {
			delete friendly_units[i];
		}

		friendly_units.clear();

		for (int i = 0; i < enemy_units.size(); i++) {
			delete enemy_units[i];
		}

		enemy_units.clear();
	}

	void drawLane(sf::RenderTarget& target) {
	}

	void spawnEnemyUnit(BaseUnit* unit) {
		unit->setup(enemyLaneSpawnPoint);
		enemy_units.push_back(unit);
	}

	void spawnFriendlyUnit(BaseUnit* unit, float offset_x) {
		unit->setup(sf::Vector2f(offset_x, enemyLaneSpawnPoint.y));
		friendly_units.push_back(unit);
	}

	BaseUnit* getEnemyUnit(const int index) {
		if (index < 0 || index >= enemy_units.size()) {
			return nullptr;
		}

		return enemy_units[index];
	}

	BaseUnit* getFriendlyUnit(const int index) {
		if (index < 0 || index >= friendly_units.size()) {
			return nullptr;
		}

		return friendly_units[index];
	}

	int getFriendlyCount() { return friendly_units.size(); }
	int getEnemyCount() { return enemy_units.size(); }

	void setSpawnPosition(sf::Vector2f position) {
		this->enemyLaneSpawnPoint = position;
	}
};