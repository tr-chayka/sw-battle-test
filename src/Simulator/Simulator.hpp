#pragma once

#include <Simulator/Commad.hpp>

namespace Sim
{
	class Simulator
	{
	public:
		void Run()
		{
			uint32_t tick = 0;
			while (Tick(tick))
				++tick;

			std::cout << "Simulation Completed" << std::endl;
		}

		void AddCommand(std::unique_ptr<BaseCommand>&& command)
		{
			commandList.emplace_back(std::move(command));
		}
	
	private:
		bool Tick(uint32_t current_tick);

	private:
		std::unique_ptr<BattleField> pBattleField{ nullptr };
		std::list<std::unique_ptr<BaseCommand>> commandList;
	};
}