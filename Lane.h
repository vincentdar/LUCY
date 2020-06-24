#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "units/Friendly.h"
#include "units/Enemies.h"
#include "Wheat.h"
#include "projectiles/Projectile.h"

#define TOTAL_LANES 5
#define ENEMY_SPAWN_X data->window.getSize().x + 100
#define BOTTOM_UI_HEIGHT 180
#define LANE_HEIGHT ((data->window.getSize().y - BOTTOM_UI_HEIGHT) / TOTAL_LANES)

class Lane
{
private:
	// Lane menyimpan semua unit yg ada 
	// Enemies
	std::vector <UNITS::Enemies*> enemy_units;

	// Friendlies
	std::vector <UNITS::Friendly*> friendly_units;

	// Projectiles
	std::vector<UNITS::Projectile*> friendly_projectiles;
	std::vector<UNITS::Projectile*> enemy_projectiles;

	// Misc
	std::vector<LUCY::Wheat*> wheatList;

	// Setiap unit hanya menyimpan value x, y nya tetap sama (1 baseline tiap lane)
	//  jadi nilai y dari vector2f ini dipakai utk spawn unit friendly dan enemy
	sf::Vector2f enemyLaneSpawnPoint;
	int x_start;

public:
	Lane(){}
	~Lane();

	// Spawner (add to vector as ptr)
	void spawnEnemyUnit(UNITS::Enemies* unit);
	void spawnEnemyProjectile(UNITS::Projectile* proj);

	void spawnFriendlyUnit(UNITS::Friendly* unit, float offset_x);
	void spawnFriendlyProjectile(UNITS::Projectile* proj);

	void spawnWheat(GameDataRef data, float offset_x);
	void removeWheat(int index);

	// Getter dari vector
	UNITS::Enemies* getEnemyUnit(int index);
	UNITS::Friendly* getFriendlyUnit(int index);
	UNITS::Projectile* getFriendlyProjectiles(int index);
	UNITS::Projectile* getEnemyProjectiles(int index);
	LUCY::Wheat* getWheat(int index);

	// Getter size
	int getFriendlyCount() { return friendly_units.size(); }
	int getEnemyCount() { return enemy_units.size(); }
	int getWheatCount() { return wheatList.size(); }
	int getEnemyProjectilesCount() { return enemy_projectiles.size(); }
	int getFriendlyProjectilesCount() { return friendly_projectiles.size(); }

	// Remove apapun yang sudah "waktunya"
	void removeDeadUnits();

	// Set spawn point lane tsb.
	void setSpawnPosition(sf::Vector2f position);
	sf::Vector2f getSpawnPosition() { return enemyLaneSpawnPoint; }

	// File serialization
	std::string LaneSerialize()
	{
		std::string buffer;
		for (auto i : friendly_units)
		{
			buffer += i->getType() + "$";
			buffer += i->StatSerialize();
			buffer += "\n";
		}
		return buffer;
		return "";
	}

	void LoadUnserialize(std::string buffer, int lane)
	{
	}
};