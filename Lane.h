#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "units/Base_Unit.h"
#include "projectiles/Projectile.h"

class Lane
{
private:
	// Lane menyimpan semua unit yg ada 
	// Enemies
	std::vector <UNITS::Base*> enemy_units;

	// Friendlies
	std::vector <UNITS::Base*> friendly_units;

	// Projectiles
	std::vector<UNITS::Projectile*> friendly_projectiles;
	std::vector<UNITS::Projectile*> enemy_projectiles;

	// Setiap unit hanya menyimpan value x : y nya tetap sama (1 baseline tiap lane)
	//  jadi nilai y dari vector2f ini dipakai utk spawn unit friendly dan enemy
	sf::Vector2f enemyLaneSpawnPoint;

public:
	Lane(){}
	~Lane();

	void spawnEnemyUnit(UNITS::Base* unit);
	void spawnEnemyProjectile(UNITS::Projectile* proj);

	void spawnFriendlyUnit(UNITS::Base* unit, float offset_x);
	void spawnFriendlyProjectile(UNITS::Projectile* proj);

	UNITS::Base* getEnemyUnit(int index);
	UNITS::Base* getFriendlyUnit(int index);

	UNITS::Projectile* getFriendlyProjectiles(int index);
	UNITS::Projectile* getEnemyProjectiles(int index);

	int getFriendlyCount() { return friendly_units.size(); }
	int getEnemyCount() { return enemy_units.size(); }

	void setSpawnPosition(sf::Vector2f position);
};