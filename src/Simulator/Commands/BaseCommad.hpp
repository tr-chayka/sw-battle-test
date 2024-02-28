#pragma once
#include <Simulator/BattleField.hpp>

#include <Units/ArcherUnit.hpp>


namespace Sim
{
	enum class CommandType
	{
		CreateMap,
		SpawnWarrior,
		SpawnArcher,
		March,
		Wait,
	};

	class BaseCommand
	{
	public:
		virtual bool Execute(std::unique_ptr<BattleField>& pBattleField) = 0; // return true if completed
		virtual ~BaseCommand() = default;
	};
}