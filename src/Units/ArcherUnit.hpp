#pragma once

#include <Actions/RangeAttackAction.hpp>
#include <Units/WarriorUnit.hpp>

namespace sw::sim
{
    class ArcherUnit : public WarriorUnit, public ICanRangeAttack
    {
    public:
        ArcherUnit(uint32_t id, const Point& position, uint32_t hp, uint32_t strength, uint32_t radius, uint32_t agility) :
            WarriorUnit(id, position, hp, strength),
            attackRadius(radius),
            agility(agility)
        {
            actionPriorityList.emplace_front(ActionType::RangeAttack);
            actionMap.emplace(ActionType::RangeAttack, std::make_shared<RangeAttackAction>(this));
        }

        virtual uint32_t getAgility() const { return agility; }
        virtual uint32_t getAttackRange() const { return attackRadius; }
        
    protected:
        uint32_t agility;
        uint32_t attackRadius;
    };
}