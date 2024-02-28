#pragma once

#include <Actions/BaseAction.hpp>
#include <Actions/Interface/RangeAttackInterface.hpp>

#include <iostream>

namespace Sim
{
    class RangeAttackAction : public BaseAction
    {
    public:
        RangeAttackAction(ICanRangeAttack* actor) :
            pActor(actor)
        {}

        virtual bool Execute(IBattleField* pBattleField)
        {
            auto pTarget = SelectTarget(pBattleField);

            if (pTarget)
            {
                pTarget->GetDamage(pActor->GetAgility());
            }

            return pTarget != nullptr;
        }

    private:
        ICanBaseAction* SelectTarget(IBattleField* pBattleField);

    private:
        ICanRangeAttack* pActor {nullptr};
    };
}