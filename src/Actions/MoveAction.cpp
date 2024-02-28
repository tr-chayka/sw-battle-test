#include <Actions/MoveAction.hpp>

#include <IO/EventLogs/UnitMoved.hpp>
#include <IO/EventLogs/MarchEnded.hpp>
#include <IO/System/EventLog.hpp>

#include <iostream>

namespace Sim
{
    static int32_t normalize(int32_t value)
    {
        return (value != 0) ? value / abs(value) : 0; 
    }

    bool MoveAction::Execute(IBattleField* pBattleField)
    {
        if (!hasDestination)
            return false;

        int32_t current_x = (int32_t)pActor->GetX();
        int32_t current_y = (int32_t)pActor->GetY();

        if (current_x == destinationX && current_y == destinationY)
            return false;

        int32_t dx = normalize(destinationX - current_x);
        int32_t dy = normalize(destinationY - current_y);

        bool result = 
            TryMoveTo(pBattleField, current_x + dx, current_y + dy) ||
            TryMoveTo(pBattleField, current_x + dx, current_y) ||
            TryMoveTo(pBattleField, current_x, current_y + dy);
        
        if (result)
        {
            sw::EventLog& logger = sw::EventLog::getLogger();

            uint32_t x = pActor->GetX();
            uint32_t y = pActor->GetY();

            logger.log(sw::io::UnitMoved{logger.getTick(), pActor->GetId(), x, y});
            if (x == destinationX && y == destinationY)
                logger.log(sw::io::MarchEnded{logger.getTick(), pActor->GetId(), x, y});
        }

        return result;
    }

    bool MoveAction::TryMoveTo(IBattleField* pBattleField, int32_t x, int32_t y)
    {
        bool result = pBattleField->IsFree(x, y);

        if (result)
        {
            pActor->SetX(x);
            pActor->SetY(y);
        }

        return result;
    }
}