#pragma once

#include <Actions/MeleeAttackAction.hpp>
#include <Units/BaseUnit.hpp>

namespace sw::sim
{
    class WarriorUnit : public BaseUnit, public ICanMeleeAttack
    {
    public:
        WarriorUnit(uint32_t id, const Point& position, uint32_t hp, uint32_t strength) :
            BaseUnit(id, position, hp),
            damageStrength(strength)
        {
            actionPriorityList.emplace_front(ActionType::MeleeAttack);
            actionMap.emplace(ActionType::MeleeAttack, std::make_shared<MeleeAttackAction>(this));    
        }
    
        virtual uint32_t getDamageStrength() const { return damageStrength; } 

    protected:
        uint32_t damageStrength;
    };
}