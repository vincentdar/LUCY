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
		currentWave = 0;
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

		if (state == SPAWNING) {
			spawnEnemy();
			enemyOnField = 0;
			state = WAITING;
		}

		//This part updates wave value
		else if (state == WAITING) {
			isEmpty = true;
			for (int i = 0; i < TOTAL_LANES; i++) {
				if (lane[i].getEnemyCount() > 0) {
					isEmpty = false;
					break;
				}
			}
			readConditions();

		}
	}

	void readConditions() {
		//This does :/
		if (isEmpty == true) {
			state = SPAWNING;
			//Change wave value
			updateWave();
			isEmpty = false;
		}
		else {
			state = WAITING;
		}
	}

	void updateWave() {
		currentWave++;

		waveEnemyCount += (rand() % 8) + 1;
	}

	void spawnEnemy() {
		//Generate random number
		enemyPicker = rand() % 4;
		lanePicker = rand() % TOTAL_LANES;
		clusterSpawn = (rand() % 4) + 1;

		//Spawn Enemy
		while (enemyOnField < waveEnemyCount) {

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
			clusterSpawn = (rand() % 4) + 1;
			respawnTimer.restart();

			if (enemyOnField >= waveEnemyCount) {
				break;
			}


			state = WAITING;
		}
	}
};