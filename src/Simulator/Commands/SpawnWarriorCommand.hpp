#pragma once

#include <Simulator/Commands/BaseCommad.hpp>
#include <Units/WarriorUnit.hpp>
#include <IO/EventLogs/UnitSpawned.hpp>
#include <IO/System/EventLog.hpp>

namespace sw::sim
{
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

		virtual bool execute(std::unique_ptr<BattleField>& pBattleField)
		{
            EventLog::getLogger().log(io::UnitSpawned{
				EventLog::getLogger().tick(), 
				unitId, 
				"Warrior", 
				unitX, 
				unitY
			});

			pBattleField->spawnUnit<WarriorUnit>(
				unitId, 
				Point{ (int32_t)unitX, (int32_t)unitY }, 
				unitHp, 
				unitStrength
			);
			
            return true;
		}

	protected:
		uint32_t unitId;
		uint32_t unitX;
		uint32_t unitY;
		uint32_t unitHp;
		uint32_t unitStrength;
	};
}