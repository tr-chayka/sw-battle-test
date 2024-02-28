#include <IO/System/CommandParser.hpp>
#include <IO/System/PrintDebug.hpp>
#include <iostream>
#include <fstream>
#include <IO/Commands/CreateMap.hpp>
#include <IO/Commands/SpawnWarrior.hpp>
#include <IO/Commands/SpawnArcher.hpp>
#include <IO/Commands/March.hpp>
#include <IO/Commands/Wait.hpp>
#include <IO/System/EventLog.hpp>
#include <IO/EventLogs/MapCreated.hpp>
#include <IO/EventLogs/UnitSpawned.hpp>
#include <IO/EventLogs/MarchStarted.hpp>
#include <IO/EventLogs/MarchEnded.hpp>
#include <IO/EventLogs/UnitMoved.hpp>
#include <IO/EventLogs/UnitDied.hpp>
#include <IO/EventLogs/UnitAttacked.hpp>


#include <Simulator/Commands/CreateBattleFieldCommand.hpp>
#include <Simulator/Commands/SpawnWarriorCommand.hpp>
#include <Simulator/Commands/SpawnArcherCommand.hpp>
#include <Simulator/Commands/MarchCommand.hpp>
#include <Simulator/Commands/WaitCommand.hpp>

#include <Simulator/Simulator.hpp>

int main(int argc, char** argv)
{
	using namespace sw;

	if (argc != 2) {
		throw std::runtime_error("Error: No file specified in command line argument");
	}

	std::ifstream file(argv[1]);
	if (!file) {
		throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
	}

	Sim::Simulator simulator;

	io::CommandParser parser;
	parser.add<io::CreateMap>(
		[&simulator](auto command)
		{
			simulator.AddCommand(std::make_unique<Sim::CreateBattleFieldCommand>(
				command.width, 
				command.height
			));
		}
		).add<io::SpawnWarrior>(
		[&simulator](auto command)
		{
			simulator.AddCommand(std::make_unique<Sim::SpawnWarriorCommand>(
				command.unitId,
				command.x,
				command.y,
				command.hp,
				command.strength
				));
		}
		).add<io::SpawnArcher>(
		[&simulator](auto command)
		{
			simulator.AddCommand(std::make_unique<Sim::SwawnArcherCommand>(
				command.unitId,
				command.x,
				command.y,
				command.hp,
				command.strength,
				command.range,
				command.agility
			));
		}
		).add<io::March>(
		[&simulator](auto command)
		{
			simulator.AddCommand(std::make_unique<Sim::MarchCommand>(
				command.unitId,
				command.targetX,
				command.targetY
			));
		}).add<io::Wait>(
		[&simulator](auto command)
		{
			simulator.AddCommand(std::make_unique<Sim::WaitCommand>(
				command.ticks
			));
		});

	parser.parse(file);

	EventLog& eventLog = EventLog::getLogger();
	eventLog.listen<io::MapCreated>([](auto& event){ printDebug(std::cout, event); });
	eventLog.listen<io::UnitSpawned>([](auto& event){ printDebug(std::cout, event); });
	eventLog.listen<io::MarchStarted>([](auto& event){ printDebug(std::cout, event); });
	eventLog.listen<io::UnitMoved>([](auto& event){ printDebug(std::cout, event); });
	eventLog.listen<io::MarchEnded>([](auto& event){ printDebug(std::cout, event); });
	eventLog.listen<io::UnitAttacked>([](auto& event){ printDebug(std::cout, event); });
	eventLog.listen<io::UnitDied>([](auto& event){ printDebug(std::cout, event); });

	simulator.Run();
	return 0;
}