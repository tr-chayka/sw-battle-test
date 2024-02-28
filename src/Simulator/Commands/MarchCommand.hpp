#pragma once

#include <Simulator/Commands/BaseCommad.hpp>
#include <IO/EventLogs/MarchStarted.hpp>
#include <IO/System/EventLog.hpp>

namespace Sim
{
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

            sw::EventLog::getLogger().log(sw::io::MarchStarted{sw::EventLog::getLogger().getTick(), unitId, pUnit->GetX(), pUnit->GetY(), destinationX, destinationY});
            return true;
		}

	private:
		uint32_t destinationX;
		uint32_t destinationY;
		uint32_t unitId;
	};
}