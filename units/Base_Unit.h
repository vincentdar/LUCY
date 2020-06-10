#pragma once

struct Position
{
	int x;
	int y;
};

class BaseUnit
{
protected:
	float HP, MP, HPRegen, MPRegen, MovementSpeed, Attack, Defend, ShieldHP;
	int Blocks;

	int id;
	Position pos;
public:
	BaseUnit() : HP(100), MP(75), HPRegen(1), MPRegen(1), MovementSpeed(1), Attack(75), Defend(50), ShieldHP(0), Blocks(1) {}

	void setUnit(float hp, float mp, float hregen, float mregen, float ms, float atk, float def, float shp, int block) {
		HP *= hp;
		MP *= mp;
		HPRegen *= hregen;
		MPRegen *= mregen;
		MovementSpeed *= ms;
		Attack *= atk;
		Defend *= def;
		ShieldHP *= shp;
		Blocks *= block;
	}

	Position GetPosition() { return pos; }

	virtual void Update() {}
};
