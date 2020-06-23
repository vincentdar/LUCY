#pragma once


namespace UNITS
{
	class Base;

	class IUnitState
	{
	protected:

		Base* unitBase;

	public:
		IUnitState(Base* base) : unitBase(base) {}

		virtual void enterState() = 0;
		virtual void processStateChanges() = 0;
		virtual void update() = 0;
		virtual void exitState() = 0;
	};

	class Attack : public IUnitState
	{
	public:
		Attack(UNITS::Base* base) : IUnitState(base) {}

		void enterState() override;
		void processStateChanges() override;
		void update() override;
		void exitState() override;
	};

	class Idle : public IUnitState
	{
	public:
		Idle(UNITS::Base* base) : IUnitState(base) {}

		void enterState() override;
		void processStateChanges() override;
		void update() override;
		void exitState() override;
	};

	class Move : public IUnitState
	{
	public:
		Move(UNITS::Base* base) : IUnitState(base) {}

		void enterState() override;
		void processStateChanges() override;
		void update() override;
		void exitState() override;
	};

	class UseSkill : public IUnitState
	{
	public:
		UseSkill(UNITS::Base* base) : IUnitState(base) {}

		void enterState() override;
		void processStateChanges() override;
		void update() override;
		void exitState() override;
	};
}