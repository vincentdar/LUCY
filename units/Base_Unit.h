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

		sf::Sound		sfx;

		// Health bar
		sf::RectangleShape	base, bar;

		sf::Clock clock;

		Base* targetedEntity = nullptr;

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

		void setUnitStats(float health, float normalDamage, float range, float ms, float as);

		sf::FloatRect getUnitBounds();
		sf::Vector2f getPosition() { return charSprite.getPosition(); }

		std::string StatSerialize() {
			return
				std::to_string(charSprite.getPosition().x) + "$" +
				std::to_string(stats.health) + "$" +
				std::to_string(stats.range) + "$" +
				std::to_string(stats.normalDamage) + "$" +
				std::to_string(stats.movementSpeed) + "$" + 
				std::to_string(stats.max_health) + "$";
		}

		void StatUnserialize(const std::string& health,
							const std::string& range, 
							const std::string& normalDamage, 
							const std::string& movementSpeed, 
							const std::string& max_health) {
			stats.health = std::stof(health);
			stats.range = std::stof(range);
			stats.normalDamage = std::stof(normalDamage);
			stats.movementSpeed = std::stof(movementSpeed);
			stats.max_health = std::stof(max_health);
		}
	};

}