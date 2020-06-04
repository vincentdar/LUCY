#pragma once

#include <SFML/Graphics.hpp>

#include "../engine/IState.h"

class MenuState
	: public LUCY::IState 
{
private:


public:
	void VInit();
	void VDraw(float dt);
	void VHandleInput();
	void VUpdate(float dt);
	void VResume();
	void VPause();
	void VExit();

	~MenuState() {}
};