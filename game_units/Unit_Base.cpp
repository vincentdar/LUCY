#include "Unit_Base.h"

#include "../Lane.h"

namespace UNITS
{
	Base::Base(GameDataRef data, Lane lanes[], int laneCount)
		: data(data), laneDataRef(lanes), laneTotal(laneCount) {}

	void Base::update()
	{
		animator.updateAnimation();

		if (stateIsChanged) {
			switch (state)
			{
			case IDLE:
				animator.playAnimation("IDLE");
				break;
			case ATTACK:
				animator.playAnimation("ATTACK");
				break;
			case HIT:
				shader.loadFromFile("res/shader/hitflash.shader", sf::Shader::Fragment);
				break;
			case DIE:
				animator.playAnimation("DIE");
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

			// Detect state changes
			for (int i = 0; i < laneDataRef[laneNumber].getEnemyCount(); i++) {
				if (laneDataRef[laneNumber].getEnemyUnit(i)
			}
		}
	}

	void Base::draw(sf::RenderTarget & target)
	{
	}

	void Base::setup(sf::Vector2f spawnPosition)
	{
		animator.bindSprite(&charSprite);

		animator.addAnimationState(
			"Idle",
			data->assets.GetTexturePtr("Archer_Green"),
			sf::IntRect(0, 51 * 1, 37, 51),
			sf::Vector2i(37, 0), 0.2, 2, true, true
		);

		animator.addAnimationState(
			"Move",
			data->assets.GetTexturePtr("Archer_Green"),
			sf::IntRect(0, 51 * 0, 37, 51),
			sf::Vector2i(37, 0), 0.2, 3, true, false
		);

		animator.addAnimationState(
			"Attack",
			data->assets.GetTexturePtr("Archer_Green"),
			sf::IntRect(0, 51 * 2, 37, 51),
			sf::Vector2i(37, 0), 0.2, 6, false, false
		);

		charSprite.setScale(2, 2);
		charSprite.setPosition(spawnPosition);
		state = IDLE;
	}

	void Base::setState(UnitState state)
	{
		this->state = state;
	}

	void Base::setUnitStats(float health, float normalDamage, float range)
	{
		stats.health = health;
		stats.normalDamage = normalDamage;
		stats.range = range;
	}
}