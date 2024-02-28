#include <Actions/MeleeAttackAction.hpp>

namespace sw::sim
{   
    ICanBaseAction* MeleeAttackAction::selectTarget(IBattleField* pBattleField)
    {
        Point actorPosition = pActor->getPosition();

        int32_t dxs[] = {-1, 0 ,1};
        int32_t dys[] = {-1, 0, 1};

        ICanBaseAction* pTarget = nullptr;

        for (int32_t dx : dxs)
            for (int32_t dy : dys)
            {
                auto possiblePosition = actorPosition + Point{ dx, dy };

                if (actorPosition == possiblePosition)
                    continue;

                auto pPossibleTarget = pBattleField->getItemByCoords(possiblePosition);
                if (pPossibleTarget == nullptr)
                    continue;

                if (pTarget == nullptr ||
                    pTarget->getHp() >= pPossibleTarget->getHp() ||
                    pTarget->getHp() == pPossibleTarget->getHp() && pTarget->getId() >= pPossibleTarget->getId())
                    pTarget = pPossibleTarget;
            }

        return pTarget;
    }
}