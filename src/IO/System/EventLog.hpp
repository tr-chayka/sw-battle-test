#pragma once

#include <iostream>
#include <typeindex>
#include <unordered_map>

namespace sw
{
	class EventLog {
	private:
		std::unordered_map<std::type_index, std::function<void(void*)>> _handlers;
		uint32_t currentTick;
		EventLog() {}

	public:
		EventLog(const EventLog&) = delete;
        void operator = (EventLog const&) = delete;

		static EventLog& getLogger();
		void setTick(uint32_t tick) { currentTick = tick; }
		uint32_t tick() const { return currentTick; }

		template <class TEvent>
		void listen(std::function<void(TEvent&)> handler)
		{
			auto [it, inserted] = _handlers.emplace(
				std::type_index(typeid(TEvent)),
				[handler = std::move(handler)](void* event)
				{
					handler(*static_cast<TEvent*>(event));
				});
			if (!inserted) {
				throw std::runtime_error("Event already exists: " + std::string(TEvent::Name));
			}
		}

		template <class TEvent>
		void log(TEvent&& event)
		{
			auto handler = _handlers.find(std::type_index(typeid(TEvent)));
			if (handler == _handlers.end())
				throw std::runtime_error("Unknown event: " + std::string(TEvent::Name));

			handler->second(&event);
		}
	};
}