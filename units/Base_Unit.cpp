#include "Base_Unit.h"

#include "../Lane.h"

namespace UNITS
{
	Base::Base(GameDataRef data, Lane lanes[], int laneCount)
		: data(data), laneDataRef(lanes), laneTotal(laneCount) {}

	void Base::update()
	{
		charSprite.setOrigin(
			charSprite.getLocalBounds().width / 2.0,
			charSprite.getLocalBounds().height
		);

		if (stateIsChanged) {
			switch (state)
			{
			case IDLE:
				animator.playAnimation("Idle");
				break;
			case ATTACK:
				animator.playAnimation("Attack");
				break;
			case HIT:
				shader.loadFromFile("res/shader/hitflash.shader", sf::Shader::Fragment);
				break;
			case MOVE:
				animator.playAnimation("Move");
				break;
			case DIE:
				animator.playAnimation("Die");
				break;
			case SKILL1:
				shader.loadFromFile("res/shader/outline.shader", sf::Shader::Fragment);
				shader.setUniform("outline_color", sf::Glsl::Vec4(sf::Color::Yellow));
				break;
			case SKILL2:
				shader.loadFromFile("res/shader/outline.shader", sf::Shader::Fragment);
				shader.setUniform("outline_color", sf::Glsl::Vec4(sf::Color::Blue));
				break;
			case SKILL3:
				shader.loadFromFile("res/shader/outline.shader", sf::Shader::Fragment);
				shader.setUniform("outline_color", sf::Glsl::Vec4(sf::Color::Cyan));
				break;
			case SKILL4:
				shader.loadFromFile("res/shader/outline.shader", sf::Shader::Fragment);
				shader.setUniform("outline_color", sf::Glsl::Vec4(sf::Color::Red));
				break;
			default:
				break;
			}

			stateIsChanged = false;
		}

		// Detect state changes
			// ATTACK -> FIND MINIMUM DISTANCE ENEMY
		/*float min = -1;
		for (int i = 0; i < laneDataRef[laneNumber].getEnemyCount(); i++) {

			float distance = laneDataRef[laneNumber].getEnemyUnit(i)->charSprite.getPosition().x - charSprite.getPosition().x;

			if (distance <= stats.range && distance <= min && distance >= 0) {
				if (state != ATTACK) {
					state = ATTACK;
					stateIsChanged = true;
				}
			}
		}

		if (min == -1) {
			if (state != IDLE) {
				state = IDLE;
				stateIsChanged = true;
			}
		}*/

		animator.updateAnimation();

	}

	void Base::draw(sf::RenderTarget & target)
	{
		if (state > 3) {
			target.draw(charSprite, &shader);
		}
		else {
			target.draw(charSprite);
		}
	}

	void Base::setState(UnitState state)
	{
		this->state = state;
		this->stateIsChanged = true;
	}

	void Base::setUnitStats(float health, float normalDamage, float range)
	{
		stats.health = health;
		stats.normalDamage = normalDamage;
		stats.range = range;
	}
}