#pragma once

#include <Simulator/Commands/BaseCommad.hpp>
#include <IO/EventLogs/MapCreated.hpp>
#include <IO/System/EventLog.hpp>

namespace sw::sim
{
    class CreateBattleFieldCommand : public BaseCommand
	{
	public:
		CreateBattleFieldCommand(uint32_t w, uint32_t h) : width(w), height(h)
		{}

		virtual bool execute(std::unique_ptr<BattleField>& pBattleField)
		{
            EventLog::getLogger().log(io::MapCreated{
				EventLog::getLogger().tick(), 
				width, height
			});
			
			pBattleField.reset(new BattleField(width, height));
			return true;
		}

	private:
		uint32_t width;
		uint32_t height;
	};
}