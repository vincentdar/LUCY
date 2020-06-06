#pragma once

class BaseUnit {
protected:
	float HP, MP, HPRegen, MPRegen, MovementSpeed, Attack, Defend, ShieldHP;
	int Blocks;
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
};