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
	float HP, MP, HPRegen, MPRegen, MovementSpeed, Attack, Defend, ShieldHP, attackUp, defenseUp;

	bool isAlive;
	bool isHit;

	// Unit visuals
	Animator			animator;
	sf::Sprite			charSprite;

	// Unit sound effects player
	sf::Sound			sound;

	// Unit shaders
	sf::Shader			shader;

	// State utk nunjukkan hrs pakai shader apa
	OutlineState		ostate;

	sf::Clock			internal_timer;
	float				time_var;

	// Utk handle window dll
	GameDataRef			data;
	sf::RenderTarget*	target;

public:
	BaseUnit(GameDataRef data) : data(data), ostate(NOSKILL)
	{
		// Setup shader
		shader.setUniform("u_texture", sf::Shader::CurrentTexture);
	}

	void setUnit(float hp, float mp, float hregen, float mregen, float ms, float atk, float def, float shp, int block) {
		HP *= hp;
		MP *= mp;
		HPRegen *= hregen;
		MPRegen *= mregen;
		MovementSpeed *= ms;
		Attack *= atk;
		Defend *= def;
		ShieldHP *= shp;
	}
	
	virtual void setup(sf::Vector2f position) = 0;

	virtual void update() = 0;

	// Fungsi draw -> bisa draw saja atau dgn tambahan shader
	virtual void draw(sf::RenderTarget& target) {

		charSprite.setOrigin(charSprite.getLocalBounds().width / 2.0, charSprite.getLocalBounds().height);

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

	void takeDamage(float damage) {

		ostate = HITFLASH;

		if (ShieldHP > 0) {

			ShieldHP -= damage;

			if (ShieldHP < 0) {
				HP += (ShieldHP - Defend - defenseUp);
				ShieldHP = 0;
			}
		}
		else
			HP -= (damage - Defend - defenseUp);

		if (HP <= 0)
			isAlive = false;

		//i still have no idea on what to do with isHit var, initially
		//initially i wanted to make it that if the unit gets hit, then isHit is set
		//to true, and then after some deltaTime then the isHit is set to false
		//this will allow the unit to do / play / activate some of the passive ability
		//the unit have
	}

	void getShieldHP(float value) {
		ShieldHP += value;
	}

	void regenEverything() {
		HP += HPRegen;
		MP += MPRegen;
	}

	void updateHPRegen(float value) {
		HPRegen += value;
	}

	void updateMPRegen(float value) {
		MPRegen += value;
	}

	void updateAttack(float value) {
		attackUp = Attack * value; //Value is the % of dmg, EG value = 0.5 which means 50%Attack
	}

	void updateDefend(float value) {
		defenseUp = Defend * value; //This will help to reset to the original value
	}

	void blockEnemy() { //this function is supposed to count how many enemy this / the unit is currently holding, if it exceds, then the new enemy will pass thru, i think a vector is needed (?)

	}
};
