#include <Actions/MeleeAttackAction.hpp>

namespace Sim
{   
    ICanBaseAction* MeleeAttackAction::SelectTarget(IBattleField* pBattleField)
    {
        int32_t actorX = pActor->GetX();
        int32_t actorY = pActor->GetY();

        int32_t dxs[] = {-1, 0 ,1};
        int32_t dys[] = {-1, 0, 1};

        ICanBaseAction* pTarget = nullptr;

        for (int32_t dx : dxs)
            for (int32_t dy : dys)
            {
                if (dx == 0 && dy == 0)
                    continue;

                auto pPossibleTarget = pBattleField->GetItemByCoords(actorX + dx, actorY + dy);
                if (pPossibleTarget == nullptr)
                    continue;

                if (pTarget == nullptr ||
                    pTarget->GetHp() >= pPossibleTarget->GetHp() ||
                    pTarget->GetHp() == pPossibleTarget->GetHp() && pTarget->GetId() >= pPossibleTarget->GetId())
                    pTarget = pPossibleTarget;
            }

        return pTarget;
    }
}