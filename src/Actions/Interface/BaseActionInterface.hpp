#pragma once

#include <cstdint>
#include <list>
#include <map>
#include <string>

#include <Utils/Point.hpp>

namespace sw::sim
{
    enum class ActionType
    {
        Move,
        MeleeAttack,
        RangeAttack,
    };

    class ICanBaseAction
    {
    public:
        virtual Point getPosition() const = 0;
        virtual uint32_t getId() const = 0;
        virtual uint32_t getHp() const = 0;
        virtual void getDamage(uint32_t damage, uint32_t from) = 0;
        
        virtual ~ICanBaseAction() = default;
    };
}