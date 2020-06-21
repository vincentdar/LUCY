#pragma once

#include "../Game.h"
#include "../Animator.h"
#include "UnitStates.h"
#include <SFML/Graphics.hpp>

using LUCY::GameDataRef;

class Lane;

namespace UNITS {

	enum UnitState { IDLE, ATTACK, MOVE, DIE, SKILL };

	struct Stats
	{
		float health;
		float range;
		float normalDamage;
		float mp;
		float movementSpeed;
	};

	class Base
	{
	protected:
		GameDataRef data;

		Stats		stats;

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

		void setUnitStats(float health, float normalDamage, float range);

		sf::FloatRect getUnitBounds() { return charSprite.getGlobalBounds(); }
		sf::Vector2f getPosition() { return charSprite.getPosition(); }
	};

}