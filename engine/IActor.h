#pragma once
#include <SFML/Graphics.hpp>

namespace LUCY
{
	class IActor
	{
	public:
		virtual void VInit() = 0;
		virtual void VHandleInput() = 0;
		virtual void VDraw(float dt) = 0;
		virtual void VUpdate(float dt) = 0;
		virtual sf::Sprite& VGetSprite() = 0;	

		virtual ~IActor() {}
	};
}


