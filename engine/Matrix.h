#pragma once
#include "../game/units/Base_Unit.h"
#include "Logger.h"

class Matrix
{
protected:
	BaseUnit* MATRIX[5][8];
public:
	Matrix();
	void AddUnit(BaseUnit* b);
	void DeleteUnit(int row, int col);
	void Update();
	BaseUnit* at(int row, int col);
	Matrix* getInstance() { return this; }
};