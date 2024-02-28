#pragma once

#include <Actions/Interface/BaseActionInterface.hpp>

namespace Sim
{
    class ICanMeleeAttack : virtual public ICanBaseAction
    {
    public:
        virtual uint32_t GetDamageStrength() const = 0;
    };
}