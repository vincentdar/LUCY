#include "Base_Unit.h"

#include "../Lane.h"
#include "..\ui\UI_Base.h"

namespace UNITS
{
	Base::Base(GameDataRef data, Lane lanes[], int laneNumber)
		: data(data), laneDataRef(lanes), laneNumber(laneNumber), laneTotal(TOTAL_LANES) {}

	void Base::update()
	{
		// Set origin ke bawah tengah
		charSprite.setOrigin(
			charSprite.getLocalBounds().width / 2.0,
			charSprite.getLocalBounds().height
		);

		// Update menurut State
		updateStateActions();

		processStateChanges();

		triggerStateChanges();

		animator.updateAnimation();
	}

	void Base::draw(sf::RenderTarget & target)
	{
		if (isHit) {
			// Override existing shader
			shader.loadFromFile("res/shader/hitflash.shader", sf::Shader::Fragment);
			target.draw(charSprite, &shader);
			isHit = false;
		}
		else if (state == SKILL) {
			target.draw(charSprite, &shader);
		}
		else {
			target.draw(charSprite);
		}
	}

	void Base::processStateChanges()
	{
		if (stateIsChanged) {
			switch (state)
			{
			case IDLE:
				animator.playAnimation("Idle");
				break;
			case ATTACK:
				animator.playAnimation("Attack");
				break;
			case MOVE:
				animator.playAnimation("Move");
				break;
			case DIE:
				//animator.playAnimation("Die");
				//printf("DIE\n");
				break;
			case SKILL:
				shader.loadFromFile("res/shader/outline.shader", sf::Shader::Fragment);
				shader.setUniform("outline_color", sf::Glsl::Vec4(sf::Color::Yellow));
				break;
			default:
				break;
			}

			stateIsChanged = false;
		}
	}

	void Base::takeDamage(int damage)
	{
		isHit = true;
		stats.health -= damage;
		if (stats.health <= 0) {
			this->setState(DIE);
		}
	}

	void Base::triggerStateChanges() {}

	void Base::updateStateActions()
	{
		
	}

	void Base::setState(UnitState state)
	{
		this->state = state;

		this->stateIsChanged = true;
	}

	void Base::setUnitStats(float health, float mp, float movementSpeed, float defense, float defenseUp, float attack, float attackUp, float attackRange, float attackSpeed, float shieldHP)
	{
		stats = { health * 100, mp, movementSpeed, defense, defenseUp, attack, attackUp, attackRange, attackSpeed, shieldHP };
	}
}