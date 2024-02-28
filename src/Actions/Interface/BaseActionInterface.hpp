#pragma once

#include <cstdint>
#include <list>
#include <map>
#include <string>

namespace Sim
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
        virtual uint32_t GetX() const = 0;
        virtual uint32_t GetY() const = 0;
        virtual uint32_t GetId() const = 0;
        virtual uint32_t GetHp() const = 0;
        virtual void GetDamage(uint32_t damage, uint32_t from) = 0;
        virtual ~ICanBaseAction() = default;
    };
}