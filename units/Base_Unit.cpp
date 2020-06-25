#include "Base_Unit.h"

#include "../Lane.h"

#define UNIT_BOUND_SIZE sf::Vector2f(60, LANE_HEIGHT)

namespace UNITS
{
	Base::Base(GameDataRef data, Lane lanes[], int laneNumber)
		: data(data), 
		laneDataRef(lanes), 
		laneNumber(laneNumber), 
		laneTotal(TOTAL_LANES) 
	{
		clock.restart();
	}

	void Base::update()
	{
		// Set origin ke bawah tengah, supaya pos sprite konsisten
		charSprite.setOrigin(
			charSprite.getLocalBounds().width / 2.0,
			charSprite.getLocalBounds().height
		);

		// Update menurut State
		processStateChanges();

		triggerStateChanges();

		updateStateActions();

		base.setPosition(charSprite.getGlobalBounds().left, charSprite.getPosition().y - charSprite.getGlobalBounds().height - 5);
		bar.setPosition(charSprite.getGlobalBounds().left, charSprite.getPosition().y - charSprite.getGlobalBounds().height - 5);
		bar.setSize(sf::Vector2f(UTILS::getValueFromRange(0, stats.max_health, 0, 1, stats.health) * 100, 10));

		animator.updateAnimation();
	}

	void Base::setup(sf::Vector2f spawnPosition) {}

	void Base::draw(sf::RenderTarget & target)
	{
		if (isHit) {
			// Override existing shader
			shader.loadFromFile("res/shader/hitflash.shader", sf::Shader::Fragment);
			//charSprite.setColor(sf::Color::Black);
			isHit = false;
			target.draw(charSprite, &shader);
			return;
		}
		
		if (skillIsActivated) {
			target.draw(charSprite, &shader);
		}
		else {
			target.draw(charSprite);
		}

		target.draw(base);
		target.draw(bar);
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
			default:
				break;
			}

			stateIsChanged = false;
		}

		if (skillIsActivated && isSkillChanged) {
			shader.loadFromFile("res/shader/outline.shader", sf::Shader::Fragment);
			shader.setUniform("outline_color", sf::Glsl::Vec4(sf::Color::Red));
			isSkillChanged = false;
		}

	}

	void Base::takeDamage(float damage)
	{
		isHit = true;
		stats.health -= damage;

		sfx.setBuffer(*data->assets.GetSoundBufferPtr("hitsfx"));
		sfx.play();

		if (stats.health <= 0) {
			this->setState(DIE);
		}
	}

	void Base::setState(UnitState state)
	{
		this->state = state;

		this->stateIsChanged = true;
	}

	void Base::setUnitStats(float health, float normalDamage, float range, float ms, float as)
	{
		stats.health = health;
		stats.normalDamage = normalDamage;
		stats.range = range;
		stats.movementSpeed = ms;
		stats.attackSpeed = as;
	}

	sf::FloatRect Base::getUnitBounds() {
		return
			sf::FloatRect(
				sf::Vector2f(
					charSprite.getPosition().x - (UNIT_BOUND_SIZE.x / 2.0),
					charSprite.getPosition().y - charSprite.getGlobalBounds().height),
				UNIT_BOUND_SIZE
			);
	}
}