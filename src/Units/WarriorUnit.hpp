#pragma once

#include <Actions/MeleeAttackAction.hpp>
#include <Units/BaseUnit.hpp>

namespace Sim
{
    class WarriorUnit : public BaseUnit, public ICanMeleeAttack
    {
    public:
        WarriorUnit(uint32_t id, uint32_t x, uint32_t y, uint32_t hp, uint32_t strength) :
            BaseUnit(id, x, y, hp),
            damageStrength(strength)
        {
            actionPriorityList.emplace_front(ActionType::MeleeAttack);
            actionMap.emplace(ActionType::MeleeAttack, std::make_shared<MeleeAttackAction>(this));    
        }
    
        virtual uint32_t GetDamageStrength() const { return damageStrength; } 

    protected:
        uint32_t damageStrength;
    };
}