#pragma once

#include <Actions/BaseAction.hpp>
#include <Actions/Interface/RangeAttackInterface.hpp>

#include <iostream>

namespace sw::sim
{
    class RangeAttackAction : public BaseAction
    {
    public:
        RangeAttackAction(ICanRangeAttack* actor) :
            pActor(actor)
        {}

        virtual bool execute(IBattleField* pBattleField)
        {
            auto pTarget = selectTarget(pBattleField);
            if (pTarget)
                pTarget->getDamage(pActor->getAgility(), pActor->getId());

            return pTarget != nullptr;
        }

    private:
        ICanBaseAction* selectTarget(IBattleField* pBattleField);

    private:
        ICanRangeAttack* pActor {nullptr};
    };
}