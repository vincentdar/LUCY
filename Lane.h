#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "units/Friendly.h"
#include "units/Enemies.h"
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

	// Setiap unit hanya menyimpan value x : y nya tetap sama (1 baseline tiap lane)
	//  jadi nilai y dari vector2f ini dipakai utk spawn unit friendly dan enemy
	sf::Vector2f enemyLaneSpawnPoint;
	int x_start;

	LUCY::GameDataRef m_data;

public:
	Lane(){}
	~Lane();

<<<<<<< HEAD
	void Initialize(LUCY::GameDataRef data)
	{
		m_data = data;
	}

=======
>>>>>>> parent of 0f3a50a... Removed unneeded files. Added units, now FIX>>??????Who knows awkaowkokaok
	void spawnEnemyUnit(UNITS::Enemies* unit);
	void spawnEnemyProjectile(UNITS::Projectile* proj);

	void spawnFriendlyUnit(UNITS::Friendly* unit, float offset_x);
	void spawnFriendlyProjectile(UNITS::Projectile* proj);

	UNITS::Enemies* getEnemyUnit(int index);
	UNITS::Friendly* getFriendlyUnit(int index);

	UNITS::Projectile* getFriendlyProjectiles(int index);
	UNITS::Projectile* getEnemyProjectiles(int index);

	int getFriendlyCount() { return friendly_units.size(); }
	int getEnemyCount() { return enemy_units.size(); }

	void removeDeadUnits();

	void setSpawnPosition(sf::Vector2f position);

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
	}

	void LoadUnserialize(std::string buffer, int lane)
	{
		
	}
};