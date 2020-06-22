#pragma once

#include "../Game.h"
#include "../Animator.h"
#include <SFML/Graphics.hpp>

using LUCY::GameDataRef;

class Lane;

namespace UNITS {

	enum UnitState { IDLE, ATTACK, MOVE, DIE, SKILL };

	struct Stats
	{
		float health;	
		float mp;
		float movementSpeed;
		
		float defense;
		float defenseUp;

		float attack;
		float attackUp;
		float attackRange;
		float attackSpeed;

		float shieldHP;	
	};

	class Base
	{
	protected:
		GameDataRef data;

		// Unit stats
		Stats		stats;
		float		doT;		// Damage over time (if any)?

		// Process State
		UnitState	state;
		bool		stateIsChanged = false;

		// Check apakah sedang kena hit (play hitflash shader)
		bool		isHit = false;

		Lane*		laneDataRef;
		int			laneNumber;
		const int	laneTotal;

		Animator	animator;
		sf::Shader	shader;

		sf::Sprite	charSprite;

		// Health bar
		sf::RectangleShape	base, bar;
		sf::Text	level;

		sf::Clock clock;

		Base(GameDataRef data, Lane lanes[], int laneNumber);
	public:

		Stats getUnitStats() { return stats; }

		virtual void update();
		virtual void setup(sf::Vector2f spawnPosition) = 0;
		virtual void draw(sf::RenderTarget& target);
		virtual void skill() = 0;

		void processStateChanges();
		virtual void takeDamage(int damage);
		virtual void triggerStateChanges();
		virtual void updateStateActions();
		void setState(UnitState state);
		UnitState getState() { return state; }

		void setUnitStats(
			float health,
			float mp,
			float movementSpeed,

			float defense,
			float defenseUp,

			float attack,
			float attackUp,
			float attackRange,
			float attackSpeed,

			float shieldHP
		);

		sf::FloatRect getUnitBounds() { return charSprite.getGlobalBounds(); }
		sf::Vector2f getPosition() { return charSprite.getPosition(); }

		float getHP() { return stats.health; }
		void setHP(float hp) { stats.health *= hp; }

		float getAtk() { return stats.attack; }
		void setAttack(float atk) { stats.attack *= atk; }

		float getDef() { return stats.defense; }
		void setDef(float def) { stats.defense *= def; }

		float getRange() { return stats.attackRange; }
		void setRange(float range) { stats.attackRange = range; }

		float getAttackSpeed() { return stats.attackSpeed; }
		void setAttackSpeed(float as) { stats.attackSpeed = as; }

		int getCurrentLane() { return laneNumber; }
		void setCurrentLane(int lane) { laneNumber = lane; }
	};

}