#pragma once

#include <Actions/BaseAction.hpp>
#include <Actions/Interface/MeleeAttackInterface.hpp>

namespace sw::sim
{
    class MeleeAttackAction : public BaseAction
    {
    public:
        MeleeAttackAction(ICanMeleeAttack* actor) :
            pActor(actor)
        {}
        
        virtual bool execute(IBattleField* pBattleField)
        {
            auto pTarget = selectTarget(pBattleField);
            if (pTarget)
                pTarget->getDamage(pActor->getDamageStrength(), pActor->getId());

            return pTarget != nullptr;
        }

    private:
       ICanBaseAction* selectTarget(IBattleField* pBattleField);

    private:
        ICanMeleeAttack* pActor {nullptr};
    };
}