#pragma once

#include <Simulator/Commands/BaseCommad.hpp>
#include <Units/WarriorUnit.hpp>
#include <IO/EventLogs/UnitSpawned.hpp>
#include <IO/System/EventLog.hpp>

namespace Sim
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

		virtual bool Execute(std::unique_ptr<BattleField>& pBattleField)
		{
            sw::EventLog::getLogger().log(sw::io::UnitSpawned{sw::EventLog::getLogger().getTick(), unitId, "Warrior", unitX, unitY});
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
}