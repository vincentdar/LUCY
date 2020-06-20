#pragma once

#include "../Game.h"
#include "../Animator.h"
#include <SFML/Graphics.hpp>

class Lane;

using LUCY::GameDataRef;

namespace UNITS {

	enum UnitState { IDLE, ATTACK, MOVE, HIT, DIE, SKILL1, SKILL2, SKILL3, SKILL4 };

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
		UnitState	state;
		bool		stateIsChanged = false;

		Lane*		laneDataRef;
		int			laneNumber;
		const int	laneTotal;

		Animator	animator;
		sf::Shader	shader;

		sf::Sprite	charSprite;

		// Health bar
		sf::RectangleShape	base,
			bar;

		Base(GameDataRef data, Lane lanes[], int laneCount = 5);

	public:

		Stats getUnitStats() { return stats; }

		virtual void update();
		virtual void setup(sf::Vector2f spawnPosition) = 0;
		virtual void draw(sf::RenderTarget& target);

		void setState(UnitState state);
		UnitState getState() { return state; }

		void setUnitStats(float health, float normalDamage, float range);

		sf::FloatRect getUnitBounds() { return charSprite.getGlobalBounds(); }
	};

}