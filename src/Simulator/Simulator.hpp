#pragma once

#include <Simulator/Commands/BaseCommad.hpp>

namespace sw::sim
{
	class Simulator
	{
	public:
		void run()
		{
			uint32_t current_tick = 0;
			while (tick(current_tick))
				current_tick++;
		}

		void addCommand(std::unique_ptr<BaseCommand>&& command)
		{
			commandList.emplace_back(std::move(command));
		}
	
	private:
		bool tick(uint32_t current_tick);

	private:
		std::unique_ptr<BattleField> pBattleField{ nullptr };
		std::list<std::unique_ptr<BaseCommand>> commandList;
	};
}