#pragma once

#include "Lane.h"

Lane::~Lane() {
	for (int i = 0; i < friendly_units.size(); i++) {
		delete friendly_units[i];
	}

	friendly_units.clear();

	for (int i = 0; i < enemy_units.size(); i++) {
		delete enemy_units[i];
	}

	enemy_units.clear();
}

void Lane::spawnEnemyUnit(UNITS::Base* unit) {
	unit->setup(enemyLaneSpawnPoint);
	enemy_units.push_back(unit);
}

void Lane::spawnEnemyProjectile(UNITS::Projectile * proj) {
	enemy_projectiles.push_back(proj);
}

void Lane::spawnFriendlyUnit(UNITS::Base* unit, float offset_x) {
	unit->setup(sf::Vector2f(offset_x, enemyLaneSpawnPoint.y));
	friendly_units.push_back(unit);
}

void Lane::spawnFriendlyProjectile(UNITS::Projectile * proj) {
	friendly_projectiles.push_back(proj);
}

UNITS::Base* Lane::getEnemyUnit(int index) {
	if (index < 0 || index >= enemy_units.size()) {
		return nullptr;
	}

	return enemy_units[index];
}

UNITS::Base* Lane::getFriendlyUnit(int index) {
	if (index < 0 || index >= friendly_units.size()) {
		return nullptr;
	}

	return friendly_units[index];
}

UNITS::Projectile * Lane::getFriendlyProjectiles(int index)
{
	if (index < 0 || index >= friendly_projectiles.size()) {
		return nullptr;
	}
	
	return friendly_projectiles[index];
}

UNITS::Projectile * Lane::getEnemyProjectiles(int index)
{
	if (index < 0 || index >= enemy_projectiles.size()) {
		return nullptr;
	}

	return enemy_projectiles[index];
}

void Lane::setSpawnPosition(sf::Vector2f position) {
	this->enemyLaneSpawnPoint = position;
}
