#include <Simulator/Simulator.hpp>

namespace Sim
{
	bool Simulator::Tick(uint32_t current_tick)
	{
		std::cout << "TICK [" << current_tick << "]" << std::endl;

		if (commandList.empty() && pBattleField->AllDied())
			return false;

		bool result = false;

		if (!commandList.empty())
		{
			auto& current_command = commandList.front();
			if (current_command->Execute(pBattleField)) {
				commandList.pop_front();
				result = true;
			}
		}

		result = pBattleField->TryDoSomethig() || result;
		pBattleField->Clean();

		return result;
	}
}