#pragma once

#include <SFML/Graphics.hpp>

#include "../Game.h"
#include "../Animator.h"

using LUCY::GameDataRef;

enum OutlineState {
	NOSKILL, HEALING, HITFLASH
};

class Walls {
	float HP;

	Animator			animator;
	sf::Sprite			charSprite;

	sf::Sound			sound;

	sf::Shader			shader;

	OutlineState		ostate;

	GameDataRef			data;
	sf::RenderTarget* target;

	sf::Clock			internal_timer;
	float				time_var;

	GameDataRef			data;
	sf::RenderTarget* target;

public:
	Walls(GameDataRef data) : data(data), ostate(NOSKILL) {
		HP = 1000;
		shader.setUniform("u_texture", sf::Shader::CurrentTexture);
	}

	void setup(sf::Vector2f position) {
		animator.bindSprite(&charSprite);
		//60 x 728
		animator.addAnimationState(
			"Stand",
			data->assets.GetTexturePtr("Wall"),
			sf::IntRect(0, 728 * 0, 60, 728),
			sf::Vector2i(60, 0), 0.2, 0, true, true);

		charSprite.setScale(1, 1);
		charSprite.setPosition(position);
		animator.playAnimation("Stand");
	}

	void update() {

	}

	void draw(sf::RenderTarget& target) {

		charSprite.setOrigin(charSprite.getLocalBounds().width / 2.0, charSprite.getLocalBounds().height);

		if (ostate == NOSKILL) {
			shader.loadFromFile("res/shader/healing.shader", sf::Shader::Fragment);
			shader.setUniform("u_time", internal_timer.getElapsedTime().asSeconds());
			target.draw(charSprite, &shader);
			return;
		}
		else {
			switch (ostate)
			{
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

	void takeDamage(float damage) {

		ostate = HITFLASH;

		HP -= damage;
	}
};