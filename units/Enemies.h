#pragma once

#include "Base_Unit.h"

namespace UNITS
{
	class Enemies : public Base 
	{
	public:
		Enemies(GameDataRef data, Lane* lane, int laneNumber) : Base(data, lane, laneNumber) {}

		void triggerStateChanges() override;
		void updateStateActions() override;
	};
}

