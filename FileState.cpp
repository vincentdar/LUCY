#include "FileState.h"

namespace LUCY {

	FileState::FileState(GameDataRef data, int mode) 
		: data(data), mode(mode) {}

	void FileState::VInit()
	{
		// Buat button
		for (int i = 0; i < 3; i++) {
			slots->setOrigin(UI::CENTERED);
			slots->setSize(sf::Vector2f(300, 300));
		}
	}

	void FileState::VDraw(float dt)
	{
	}

	void FileState::VHandleInput()
	{
	}

	void FileState::VUpdate(float dt)
	{
	}

	void FileState::VResume()
	{
	}

	void FileState::VPause()
	{
	}

	void FileState::VExit()
	{
	}



}
