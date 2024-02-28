#pragma once

#include <Actions/BaseAction.hpp>
#include <Actions/Interface/MeleeAttackInterface.hpp>

#include <iostream>

namespace Sim
{
    class MeleeAttackAction : public BaseAction
    {
    public:
        MeleeAttackAction(ICanMeleeAttack* actor) :
            pActor(actor)
        {}
        
        virtual bool Execute(IBattleField* pBattleField)
        {
            auto pTarget = SelectTarget(pBattleField);

            if (pTarget)
            {
                pTarget->GetDamage(pActor->GetDamageStrength());
                
                // debug print
                std::cout
                    << "UNIT [" << pActor->GetId()
                    << "] damaged UNIT [" << pTarget->GetId()
                    << "] in melee and deal [" << pActor->GetDamageStrength() << "] damage"
                    << std::endl;

                // debug print
            }  

            return pTarget != nullptr;
        }

    private:
       ICanBaseAction* SelectTarget(IBattleField* pBattleField);

    private:
        ICanMeleeAttack* pActor {nullptr};
    };
}