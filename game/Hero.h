#pragma once
#include "../engine/IActor.h"
#include "../engine/Game.h"
#include "../engine/Animation.h"
#include "../engine/Physics.h"

namespace LUCY
{
	class Hero: public IActor
	{
	private:
		GameDataRef m_data;

		sf::Texture m_textureR;
		sf::Texture m_textureL;
		sf::Sprite m_sprite;

		//COMPONENTS
		//ANIMATION
		Animation anim;
		bool m_isIdle = true;
		bool m_isRunning = false;
		bool m_isAttacking = false;
		bool m_isRight = true;						//hero orientation

		//PHYSICS
		Physics physics;
		float m_stamina = 5.0f;
	public:
		Hero(GameDataRef data);
		virtual void VInit();
		virtual void VHandleInput();
		virtual void VDraw(float dt);
		virtual void VUpdate(float dt);
		virtual sf::Sprite& VGetSprite();
	};
}


