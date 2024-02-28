#include <Actions/MoveAction.hpp>

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


        return
            TryMoveTo(pBattleField, current_x + dx, current_y + dy) ||
            TryMoveTo(pBattleField, current_x + dx, current_y) ||
            TryMoveTo(pBattleField, current_x, current_y + dy);
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