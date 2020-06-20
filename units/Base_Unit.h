#pragma once

#include <SFML/Graphics.hpp>

#include "Base_Unit.h"
#include "../Game.h"
#include "../Animator.h"

using LUCY::GameDataRef;

// Enum untk set outline warna apa yg keluar. (Tiap state beda outline color)
enum OutlineState {
	NOSKILL, SKILL1, SKILL2, SKILL3, SKILL4, HEALING, HITFLASH
};

class BaseUnit
{
protected:
	float HP, Attack, Defend, attackRange, dot, attackSpeed;
	int currentLane;

	bool isAlive;
	bool isStunned;

	// Unit visuals
	Animator animator;
	sf::Sprite charSprite;

	// Unit sound effects player
	sf::Sound sound;

	// Unit shaders
	sf::Shader shader;

	// State utk nunjukkan hrs pakai shader apa
	OutlineState ostate;

	sf::Clock internal_timer;
	float time_var;

	sf::RenderTarget *target; //idk how to use this

	// Utk handle window dll
	GameDataRef data;

public:
	BaseUnit(GameDataRef data) : data(data), ostate(NOSKILL)
	{
		// Setup shader
		shader.setUniform("u_texture", sf::Shader::CurrentTexture);
	}

	virtual void setUnit(float hp, float atk, float def, int block, float range, float doT, int lane, float as) {
		HP *= hp;
		Attack *= atk;
		Defend *= def;
		attackRange = range;
		dot = doT;
		currentLane = lane;
		attackSpeed = as;
	}

	int getCurrentLane() { return currentLane; }
	void setCurrentLane(int lane) { currentLane = lane; }
	
	void setDoT(float dt) { dot = dt; }
	float getDoT() { return dot; }

	virtual void setup(sf::Vector2f position) = 0;
	virtual void update() = 0;

	// Fungsi draw -> bisa draw saja atau dgn tambahan shader
	virtual void draw(sf::RenderTarget& target) {

		if (ostate == NOSKILL) {
			target.draw(charSprite);
			return;
		}
		else {
			switch (ostate)
			{
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
			case HEALING:
				shader.loadFromFile("res/shader/outline.shader", sf::Shader::Fragment);
				shader.setUniform("outline_color", sf::Glsl::Vec4(sf::Color::Green));
				break;
			case HITFLASH:
				shader.loadFromFile("res/shader/hitflash.shader", sf::Shader::Fragment);
				break;
			default:
				break;
			}
		}
		target.draw(charSprite, &shader);
	}

	void setOutlineState(OutlineState state) {
		ostate = state;
	}

	void setAnimationState(const std::string& anim_key) {
		animator.playAnimation(anim_key);
	}

	virtual void attack() = 0;
	virtual void run() = 0;
	
	virtual void idle() {}
	virtual void die() {}

	virtual void takeDamage(float damage) {
		HP -= damage;

		if (HP <= 0)
			isAlive = false;
		ostate = HITFLASH;
	}

	void blockEnemy() { //this function is supposed to count how many enemy this / the unit is currently holding, if it exceds, then the new enemy will pass thru, i think a vector is needed (?)

	}

	virtual void Skill1() {}
	virtual void Skill2() {}
	virtual void Ultimate() {}
	virtual void Skill3() {}
};
