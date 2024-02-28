#pragma once

#include <Actions/Interface/BaseActionInterface.hpp>

namespace Sim
{
    class ICanRangeAttack : virtual public ICanBaseAction
    {
    public:
        virtual uint32_t GetAttackRange() const = 0;
        virtual uint32_t GetAgility() const = 0;
    };
}