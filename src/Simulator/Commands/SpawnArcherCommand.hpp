#pragma once

#include <Simulator/Commands/SpawnWarriorCommand.hpp>

namespace sw::sim
{
    class SpawnArcherCommand : public SpawnWarriorCommand
	{
	public:
		SpawnArcherCommand(uint32_t id, uint32_t x, uint32_t y, uint32_t hp, uint32_t strength, uint32_t range, uint32_t agility) :
			SpawnWarriorCommand(id, x, y, hp, strength),
			unitRange(range),
			unitAgility(agility)
		{}

		virtual bool execute(std::unique_ptr<BattleField>& pBattleField)
		{
			EventLog::getLogger().log(io::UnitSpawned{
				EventLog::getLogger().tick(), 
				unitId, 
				"Archer", 
				unitX, 
				unitY
			});

			pBattleField->spawnUnit<ArcherUnit>(
				unitId, 
				Point{ (int32_t)unitX, (int32_t)unitY }, 
				unitHp, 
				unitStrength, 
				unitRange, 
				unitAgility
			);

			return true;
		}

	protected:
		uint32_t unitRange;
		uint32_t unitAgility;
	};
}