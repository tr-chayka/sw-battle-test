#pragma once

#include <Simulator/BattleField.hpp>
#include <Units/ArcherUnit.hpp>

namespace sw::sim
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
		virtual bool execute(std::unique_ptr<BattleField>& pBattleField) = 0; // return true if completed
		virtual ~BaseCommand() = default;
	};

	using UPBaseCommand = std::unique_ptr<BaseCommand>;
}