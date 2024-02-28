#include <Actions/MoveAction.hpp>

#include <IO/EventLogs/UnitMoved.hpp>
#include <IO/EventLogs/MarchEnded.hpp>
#include <IO/System/EventLog.hpp>

#include <iostream>

namespace sw::sim
{
    bool MoveAction::execute(IBattleField* pBattleField)
    {
        if (!hasDestination)
            return false;

        auto currentPosition = pActor->getPosition();
        if (currentPosition == destinationPoint)
            return false;

        auto shift = (destinationPoint - currentPosition).norm();

        bool result = 
            tryMoveTo(pBattleField, currentPosition + shift) ||
            tryMoveTo(pBattleField, currentPosition + Point{ shift.x, 0 }) ||
            tryMoveTo(pBattleField, currentPosition + Point{ 0, shift.y });
        
        if (result)
        {
            currentPosition = pActor->getPosition();

            EventLog& logger = EventLog::getLogger();
            logger.log(io::UnitMoved{
                logger.tick(), 
                pActor->getId(), 
                (uint32_t)currentPosition.x, 
                (uint32_t)currentPosition.y
            });
            
            if (currentPosition == destinationPoint)
                logger.log(io::MarchEnded{
                    logger.tick(), 
                    pActor->getId(), 
                    (uint32_t)currentPosition.x, 
                    (uint32_t)currentPosition.y
            });
        }

        return result;
    }

    bool MoveAction::tryMoveTo(IBattleField* pBattleField, const Point& position)
    {
        if (pBattleField->isFree(position))
        {
            pActor->setPosition(position);
            return true;
        }

        return false;
    }
}