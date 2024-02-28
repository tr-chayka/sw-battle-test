#include <Simulator/Simulator.hpp>
#include <IO/System/EventLog.hpp>

namespace sw::sim
{
	bool Simulator::tick(uint32_t current_tick)
	{
		EventLog::getLogger().setTick(current_tick);

		if (commandList.empty() && pBattleField->allDied())
			return false;

		bool result = false;
		if (!commandList.empty())
		{
			result = true;
			auto& current_command = commandList.front();
			if (current_command->execute(pBattleField)) {
				commandList.pop_front();
			}
		}

		result = pBattleField->tryDoSomethig() || result;
		pBattleField->clean();

		return result;
	}
}