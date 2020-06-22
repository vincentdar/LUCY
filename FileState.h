#pragma once

#include "IState.h"
#include "Game.h"
#include "ui/UI_Button.h"

namespace LUCY
{
	class FileState 
		: public IState
	{
	private:
		GameDataRef data;
		UI::Button slots[3];
		int mode; // Mode 0: save, 1: load

	public:
		FileState(GameDataRef data, int mode = 0);
		virtual void VInit();
		virtual void VDraw(float dt);
		virtual void VHandleInput();
		virtual void VUpdate(float dt);
		virtual void VResume();
		virtual void VPause();
		virtual void VExit();
	};
}