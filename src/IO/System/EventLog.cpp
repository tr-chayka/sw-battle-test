#include <IO/System/EventLog.hpp>

namespace sw
{
    EventLog& EventLog::getLogger()
	{
		static EventLog logger;
		return logger;
	}
}