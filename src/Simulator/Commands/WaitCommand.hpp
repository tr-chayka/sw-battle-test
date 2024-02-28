#pragma once

#include <Simulator/Commands/BaseCommad.hpp>

namespace sw::sim
{
    class WaitCommand : public BaseCommand
	{
	public:
		WaitCommand(uint32_t time) : waitTime(time)
		{}

		virtual bool execute(std::unique_ptr<BattleField>& pBattleField)
		{
			if (waitTime == 0)
				return true;
			else
				waitTime--;
			
			return false;
		}

	private:
		uint32_t waitTime;
	};
}