#include <Simulator/Simulator.hpp>
#include <IO/System/EventLog.hpp>

namespace Sim
{
	bool Simulator::Tick(uint32_t current_tick)
	{
		sw::EventLog::getLogger().setTick(current_tick);

		if (commandList.empty() && pBattleField->AllDied())
			return false;

		bool result = false;
		if (!commandList.empty())
		{
			result = true;
			auto& current_command = commandList.front();
			if (current_command->Execute(pBattleField)) {
				commandList.pop_front();
			}
		}

		result = pBattleField->TryDoSomethig() || result;
		pBattleField->Clean();

		return result;
	}
}