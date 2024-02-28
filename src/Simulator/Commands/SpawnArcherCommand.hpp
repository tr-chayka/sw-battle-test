#pragma once

#include <Simulator/Commands/SpawnWarriorCommand.hpp>

namespace Sim
{
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
			sw::EventLog::getLogger().log(sw::io::UnitSpawned{sw::EventLog::getLogger().getTick(), unitId, "Archer", unitX, unitY});
			pBattleField->SpawnUnit<ArcherUnit>(unitId, unitX, unitY, unitHp, unitStrength, unitRange, unitAgility);
			return true;
		}

	protected:
		uint32_t unitRange;
		uint32_t unitAgility;
	};
}