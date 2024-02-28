#pragma once

#include <Actions/Interface/BaseActionInterface.hpp>

namespace sw::sim
{
    class ICanMeleeAttack : virtual public ICanBaseAction
    {
    public:
        virtual uint32_t getDamageStrength() const = 0;
    };
}