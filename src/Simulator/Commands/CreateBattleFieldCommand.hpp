#pragma once

#include <Simulator/Commands/BaseCommad.hpp>
#include <IO/EventLogs/MapCreated.hpp>
#include <IO/System/EventLog.hpp>

namespace Sim
{
    class CreateBattleFieldCommand : public BaseCommand
	{
	public:
		CreateBattleFieldCommand(uint32_t w, uint32_t h) : width(w), height(h)
		{}

		virtual bool Execute(std::unique_ptr<BattleField>& pBattleField)
		{
            sw::EventLog::getLogger().log(sw::io::MapCreated{sw::EventLog::getLogger().getTick(), width, height});
			pBattleField.reset(new BattleField(width, height));
			return true;
		}

	private:
		uint32_t width;
		uint32_t height;
	};
}