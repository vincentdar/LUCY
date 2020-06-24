#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "units/Friendly.h"
#include "units/Enemies.h"
#include "Wheat.h"
#include "projectiles/Projectile.h"

// Macro utk lane ada di Macro.h

class Lane
{
private:
	// Lane menyimpan semua unit yg ada 
	// Enemies
	std::vector <UNITS::Enemies*> enemy_units;

	// Friendlies
	std::vector <UNITS::Friendly*> friendly_units;

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
	void spawnFriendlyUnit(UNITS::Friendly* unit, float offset_x);
	void spawnWheat(GameDataRef data, float offset_x);


	// Getter dari vector
	UNITS::Enemies* getEnemyUnit(int index);
	UNITS::Friendly* getFriendlyUnit(int index);
	LUCY::Wheat* getWheat(int index);

	// Getter size
	int getFriendlyCount() { return friendly_units.size(); }
	int getEnemyCount() { return enemy_units.size(); }
	int getWheatCount() { return wheatList.size(); }

	// Remove apapun yang sudah "waktunya"
	void removeDeadUnits();
	void removeWheat(int index);

	// Set spawn point lane tsb.
	void setSpawnPosition(sf::Vector2f position);
	sf::Vector2f getSpawnPosition() { return enemyLaneSpawnPoint; }

	// Serialization data utk disave ke file txt (load game)
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