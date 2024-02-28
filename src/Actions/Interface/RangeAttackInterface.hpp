#pragma once

#include <Actions/Interface/BaseActionInterface.hpp>

namespace sw::sim
{
    class ICanRangeAttack : virtual public ICanBaseAction
    {
    public:
        virtual uint32_t getAttackRange() const = 0;
        virtual uint32_t getAgility() const = 0;
    };
}