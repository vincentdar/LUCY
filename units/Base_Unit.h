#pragma once

#include "../Game.h"
#include "../Animator.h"
#include <SFML/Graphics.hpp>

using LUCY::GameDataRef;

class Lane;

namespace UNITS {

	enum UnitState { IDLE, ATTACK, MOVE, DIE };

	struct Stats
	{
		float health;
		float range;
		float normalDamage;
		float movementSpeed;
		float attackSpeed;
		float max_health;
	};

	class Base
	{
	protected:
		GameDataRef		data;

		Stats			stats;
		bool			skillIsActivated = false;

		// Process State
		UnitState		state;
		bool			stateIsChanged = false;

		// Check apakah sedang kena hit (play hitflash shader)
		bool			isHit = false;

		Lane*			laneDataRef;
		int				laneNumber;
		const int		laneTotal;

		Animator		animator;
		sf::Shader		shader;

		sf::Sprite		charSprite;
		sf::FloatRect	unitBounds;

		// Health bar
		sf::RectangleShape	base, bar;

		sf::Clock clock;

		Base(GameDataRef data, Lane lanes[], int laneNumber);
	public:

		Stats getUnitStats() { return stats; }

		virtual void update();
		virtual void setup(sf::Vector2f spawnPosition);
		virtual void draw(sf::RenderTarget& target);
		virtual void skill() = 0;

		virtual void processStateChanges();
		virtual void takeDamage(int damage);
		virtual void triggerStateChanges() {}
		virtual void updateStateActions() {}
		void setState(UnitState state);
		UnitState getState() { return state; }

		void setUnitStats(float health, float normalDamage, float range);

		sf::FloatRect getUnitBounds();
		sf::Vector2f getPosition() { return charSprite.getPosition(); }
	};

}