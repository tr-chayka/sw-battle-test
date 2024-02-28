#include <Actions/RangeAttackAction.hpp>

namespace sw::sim
{
    ICanBaseAction* RangeAttackAction::selectTarget(IBattleField* pBattleField)
    {
        ICanBaseAction* pTarget = nullptr;
        
        auto range = pActor->getAttackRange();
        auto currentPosition = pActor->getPosition();

        for (int32_t x = currentPosition.x - range; x <= currentPosition.x + range; x++)
            for (int32_t y = currentPosition.y - range; y <= currentPosition.y + range; y++)
            {
                auto possiblePosition = Point{ x, y };
                auto distance2 = possiblePosition.distance2(currentPosition);
                if (distance2 < 4 || distance2 > range * range)
                    continue;

                auto pPossibleTarget = pBattleField->getItemByCoords(possiblePosition);
                if (pPossibleTarget)
                {
                    if (pTarget == nullptr)
                        pTarget = pPossibleTarget;
                    else
                    {
                        auto targetPosition = pTarget->getPosition();
                        if (currentPosition.distance2(possiblePosition) < currentPosition.distance2(targetPosition))
                            pTarget = pPossibleTarget;
                        else if (pPossibleTarget->getHp() < pTarget->getHp() ||
                            pPossibleTarget->getHp() == pTarget->getHp() &&
                            pPossibleTarget->getId() < pTarget->getId())
                            pTarget = pPossibleTarget;
                    }
                }
            }

        return pTarget;
   }
}