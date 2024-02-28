#pragma once

#include <Simulator/Commands/BaseCommad.hpp>
#include <IO/EventLogs/MarchStarted.hpp>
#include <IO/System/EventLog.hpp>

namespace sw::sim
{
    class MarchCommand : public BaseCommand
	{
	public:
		MarchCommand(uint32_t id, uint32_t x, uint32_t y) :
			unitId(id),
			destX(x),
			destY(y)
		{}

		virtual bool execute(std::unique_ptr<BattleField>& pBattleField)
		{
			auto pUnit = pBattleField->getUnit(unitId);
			if (pUnit == nullptr)
				return true;

			auto pAction = pUnit->getAction(ActionType::Move);
			if (pAction == nullptr)
				return true;

			// dynamic_cast ...
			((MoveAction*)pAction.get())->setDestination(Point{ (int32_t)destX, (int32_t)destY });

            EventLog::getLogger().log(io::MarchStarted{
				EventLog::getLogger().tick(), 
				unitId, 
				(uint32_t)pUnit->getPosition().x,
				(uint32_t)pUnit->getPosition().y,
				destX,
				destY
			});

            return true;
		}

	private:
		uint32_t destX;
		uint32_t destY;
		uint32_t unitId;
	};
}