#pragma once

#include <Actions/Interface/BaseActionInterface.hpp>

namespace Sim
{
    class IBattleField
    {
    public:
        virtual bool IsFree(uint32_t x, uint32_t y) const = 0;
        virtual bool IsValidCoords(uint32_t x, uint32_t y) const = 0;

        virtual ICanBaseAction* GetItemByCoords(uint32_t x, uint32_t y) = 0;
        virtual ICanBaseAction* GetItemById(uint32_t id) = 0;
    };
}