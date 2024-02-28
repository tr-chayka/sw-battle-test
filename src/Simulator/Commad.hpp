#pragma once
#include <Simulator/BattleField.hpp>
#include <Units/WarriorUnit.hpp>
#include <Units/ArcherUnit.hpp>

namespace Sim
{
	enum class CommandType
	{
		CreateMap,
		SpawnWarrior,
		SpawnArcher,
		March,
		Wait,
	};

	class BaseCommand
	{
	public:
		virtual bool Execute(std::unique_ptr<BattleField>& pBattleField) = 0; // return true if completed
	protected:
		CommandType CommandType; // not needed at all ?
	};

	class CreateBattleFieldCommand : public BaseCommand
	{
	public:
		CreateBattleFieldCommand(uint32_t w, uint32_t h) : width(w), height(h)
		{}

		virtual bool Execute(std::unique_ptr<BattleField>& pBattleField)
		{
			std::cout << "MAP_CREATED with WIDTH = " << width << " and HEIGHT = " << height << std::endl;
			pBattleField.reset(new BattleField(width, height));
			return true;
		}

	private:
		uint32_t width;
		uint32_t height;
	};

	class SpawnWarriorCommand : public BaseCommand
	{
	public:
		SpawnWarriorCommand(uint32_t id, uint32_t x, uint32_t y, uint32_t hp, uint32_t strength) :
			unitId(id),
			unitX(x),
			unitY(y),
			unitHp(hp),
			unitStrength(strength)
		{}

		virtual bool Execute(std::unique_ptr<BattleField>& pBattleField)
		{
			std::cout
				<< "WARRIOR_SPAWNED "
				<< "Id = " << unitId
				<< " X = " << unitX
				<< " Y = " << unitY
				<< " Hp = " << unitHp
				<< " Strength = " << unitStrength
				<< std::endl;

			pBattleField->SpawnUnit<WarriorUnit>(unitId, unitX, unitY, unitHp, unitStrength);
			return true;
		}

	protected:
		uint32_t unitId;
		uint32_t unitX;
		uint32_t unitY;
		uint32_t unitHp;
		uint32_t unitStrength;
	};

	class SwawnArcherCommand : public SpawnWarriorCommand
	{
	public:
		SwawnArcherCommand(uint32_t id, uint32_t x, uint32_t y, uint32_t hp, uint32_t strength, uint32_t range, uint32_t agility) :
			SpawnWarriorCommand(id, x, y, hp, strength),
			unitRange(range),
			unitAgility(agility)
		{}

		virtual bool Execute(std::unique_ptr<BattleField>& pBattleField)
		{
			pBattleField->SpawnUnit<ArcherUnit>(unitId, unitX, unitY, unitHp, unitStrength, unitRange, unitAgility);
			return true;
		}

	protected:
		uint32_t unitRange;
		uint32_t unitAgility;
	};

	class WaitCommand : public BaseCommand
	{
	public:
		WaitCommand(uint32_t time) : waitTime(time)
		{}

		virtual bool Execute(std::unique_ptr<BattleField>& pBattleField)
		{
			if (waitTime == 0)
				return true;
			else
				--waitTime;
			
			return false;
		}

	private:
		uint32_t waitTime;
	};

	class MarchCommand : public BaseCommand
	{
	public:
		MarchCommand(uint32_t id, uint32_t x, uint32_t y) :
			unitId(id),
			destinationX(x),
			destinationY(y)
		{}

		virtual bool Execute(std::unique_ptr<BattleField>& pBattleField)
		{
			auto pUnit = pBattleField->GetUnit(unitId);
			if (pUnit == nullptr)
				return true;

			auto pAction = pUnit->GetAction(ActionType::Move);
			if (pAction == nullptr)
				return true;

			// dynamic_cast ...
			((MoveAction*)pAction.get())->SetDestination(destinationX, destinationY);
			return true;
		}

	private:
		uint32_t destinationX;
		uint32_t destinationY;
		uint32_t unitId;
	};
}