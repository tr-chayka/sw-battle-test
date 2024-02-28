#include <Actions/RangeAttackAction.hpp>

namespace Sim
{
    static int32_t length2(int32_t x, int32_t y)
    {
        return x * x + y * y;
    }

    static int32_t distance2(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
    {
        return length2(x2 - x1, y2 - y1);
    }

    ICanBaseAction* RangeAttackAction::SelectTarget(IBattleField* pBattleField)
    {
        ICanBaseAction* pTarget = nullptr;
        
        int32_t range = pActor->GetAttackRange();
        int32_t current_x = pActor->GetX();
        int32_t current_y = pActor->GetY();

        for (int32_t x = current_x - range; x <= current_x + range; ++x)
            for (int32_t y = current_y - range; y <= current_y + range; ++y)
            {
                int32_t l2 = length2(x - current_x, y - current_y);
                if (l2 < 4 || l2 > range * range)
                    continue;

                auto pPossibleTarget = pBattleField->GetItemByCoords(x, y);
                if (pPossibleTarget)
                {
                    if (pTarget == nullptr)
                    {
                        pTarget = pPossibleTarget;
                    }
                    else
                    {
                        int32_t target_distance2 = distance2(pTarget->GetX(), pTarget->GetY(), current_x, current_y);
                        int32_t possible_distance2 = distance2(pPossibleTarget->GetX(), pPossibleTarget->GetY(), current_x, current_y);
                        
                        if (possible_distance2 < target_distance2)
                        {
                            pTarget = pPossibleTarget;
                        }
                        else if (possible_distance2 == target_distance2)
                        {
                            if (pPossibleTarget->GetHp() <= pTarget->GetHp() ||
                                pPossibleTarget->GetHp() == pTarget->GetHp() && pPossibleTarget->GetId() <= pPossibleTarget->GetId())
                                pTarget = pPossibleTarget;

                        }
                    }
                }
            }

        return pTarget;
    }
}