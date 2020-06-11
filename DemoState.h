#pragma once
#include "IState.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Hero.h"
#include "units/GoldenKnight.h"
#include "units/Archer.h"
#include "units/Spearmen.h"
#include "ui/UI_Board.h"
#include "ui/UI_Button.h"

namespace LUCY
{
	class DemoState : public IState
	{
	private:
		sf::Clock m_clock;
		sf::Sprite m_background;
		GameDataRef m_data;

		Archer archer;
		Spearmen spearman;

		UI::Board board;
		UI::Button button;

		//Hero m_hero;
	public:
		DemoState(GameDataRef data);
		virtual void VInit();
		virtual void VDraw(float dt);
		virtual void VHandleInput();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();

		

	};

	// Buat function utk di dlm onClick sm onHover diluar class ya.. Klo gk mau inline 
	//   bisa definisiin void click(); disini trs isi functionnya di .cpp atau lek wani pake lambda
	inline void click() {
		printf("Hello Worudo!\n");
	}
	
}


