#pragma once

#include "Lane.h"
#include "units/Enemy/EvilArcher.h"
#include "units/Enemy/EvilAssassin.h"
#include "units/Enemy/EvilSpearmen.h"
#include "units/Enemy/EvilKnight.h"

#include "units/Enemies.h"


//How to use
//1. Check state first
//2. Read conditions comes seconds


class Spawner {
private:
	enum SPAWNER_STATE { SPAWNING, WAITING };

	//Primary Attribute
	int currentWave; //Self explanatory
	int waveEnemyCount; //Unit Cap per wave
	int enemyOnField;
	int enemyPicker; //EnemyRandomizer
	int lanePicker; //LaneRandomizer
	int clusterSpawn; //Multiplespawn at once, set to max 5

	bool isEmpty; //Lane Checker, Mainly for all lanes

	sf::Clock respawnTimer;

	SPAWNER_STATE state;

	Lane* lane;
	GameDataRef data;

	Wall* wall;

	//Modifying Variable
	float attributeModifier; //Per wave enemy gets an upgrade on stats
	int waveEnemyModifier; //Per wave more enemy is getting spawned
	//Those 2 variables are not implemented yet, hopefully in the near future


public:
	Spawner(Lane* lane, GameDataRef data, Wall* wall) : lane(lane), data(data), wall(wall) {
		currentWave = 1;
		waveEnemyCount = 5;
		enemyOnField = 0;
		enemyPicker = -1;
		lanePicker = -1;
		clusterSpawn = 0;

		attributeModifier = 0;
		waveEnemyCount = 0;
		respawnTimer.restart();

		state = WAITING;

		isEmpty = true;
	}

	int getCurrentWave() { return currentWave; }
	void setCurrentWave(int value) { currentWave = value; }

	void checkState() {
		std::cout << "START OF CHECKSTATE\n";

		if (state == SPAWNING) {
			std::cout << "SPAWNS ENEMY!\n";
			spawnEnemy();
			enemyOnField = 0;
			state = WAITING;

		}

		//This part updates wave value
		else if (state == WAITING) {
			isEmpty = true;
			std::cout << "WAITING\n";
			for (int i = 0; i < TOTAL_LANES; i++) {
				if (lane[i].getEnemyCount() > 0) {
					isEmpty = false;
					break;
				}
			}
			//Well not EXACTLY this lmao
			readConditions();

		}

		std::cout << "END OF CHECKSTATE\n";
	}

	void readConditions() {
		//This does :/
		if (isEmpty == true) {
			state = SPAWNING;
			//Change wave value
			updateWave();
			isEmpty = false;
			std::cout << "ARENA IS EMPTY\n";
		}
		else {
			state = WAITING;
			std::cout << "ARENA IS NOT EMPTY\n";
		}
	}

	void updateWave() {
		currentWave++;

		//Making it consistent (?)
		/*
		if (currentWave >= 10) {
			for (int i = 0; i < INT_MAX; i++) {
				if (waveEnemyCount >= i * 1 && waveEnemyCount < i * 2) {
					waveEnemyCount = i;
					break;
				}
			}
		}*/ //This function is kinda confusing not gonna lie, why did i make this ? :/

		waveEnemyCount += (rand() % 8) + 1;
	}
	void spawnEnemy() {
		std::cout << "START SPAWNING\n";
		//Generate random number
		enemyPicker = rand() % 4;
		lanePicker = rand() % TOTAL_LANES;
		clusterSpawn = (rand() % 4) + 1;

		//Spawn Enemy
		while (enemyOnField < waveEnemyCount) {
			if (respawnTimer.getElapsedTime().asSeconds() >= 0.5) {
				std::cout << "SPAWNS\n";
				for (int i = 0; i < clusterSpawn; i++) {
					if (enemyPicker == 0) {
						lane[lanePicker].spawnEnemyUnit(new UNITS::EvilAssassin(data, lane, lanePicker, wall));
					}
					else if (enemyPicker == 1) {
						lane[lanePicker].spawnEnemyUnit(new UNITS::EvilKnight(data, lane, lanePicker, wall));
					}
					else if (enemyPicker == 2) {
						lane[lanePicker].spawnEnemyUnit(new UNITS::EvilSpearmen(data, lane, lanePicker, wall));
					}
					else if (enemyPicker == 3) {
						lane[lanePicker].spawnEnemyUnit(new UNITS::EvilArcher(data, lane, lanePicker, wall));
					}
					enemyPicker = rand() % 4;
					lanePicker = rand() % TOTAL_LANES;
				}

				enemyOnField += clusterSpawn;
				std::cout << "SPAWNED " << clusterSpawn << " ENEMIES\n";
				clusterSpawn = (rand() % 4) + 1;
				respawnTimer.restart();
			}



			if (enemyOnField >= waveEnemyCount) {
				std::cout << "UNIT COUNT MAXED OUT\n";
				break;
			}
		}

		state = WAITING;
	}
};