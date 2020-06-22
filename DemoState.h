//#pragma once
//#include "IState.h"
//#include "Game.h"
//#include <SFML/Graphics.hpp>
//#include "units/Friendly/GoldenKnight.h"
//#include "units/Friendly/Archer.h"
//#include "units/Friendly/Spearman.h"
//#include "units/Friendly/Assassin.h"
//#include "ui/UI_Button.h"
//#include "ui/UI_Textfield.h"
//#include "Camera.h"
//
//namespace LUCY
//{
//	class DemoState : public IState
//	{
//	private:
//		sf::Clock m_clock;
//		sf::Sprite m_background;
//		GameDataRef m_data;
//
//		std::vector<UNITS::Base*> units;
//
//		UI::Textfield field;
//
//		sf::Shader sh;
//
//		Camera cam;
//
//		std::string str = "";
//
//		//Hero m_hero;
//	public:
//		DemoState(GameDataRef data);
//		virtual void VInit();
//		virtual void VDraw(float dt);
//		virtual void VHandleInput();
//		virtual void VUpdate(float dt);
//		virtual void VResume();
//		virtual void VPause();
//		virtual void VExit();
//	};
//}
//
//
