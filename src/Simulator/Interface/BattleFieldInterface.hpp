#pragma once

#include <Actions/Interface/BaseActionInterface.hpp>

namespace sw::sim
{
    class IBattleField
    {
    public:
        virtual bool isFree(const Point& position) const = 0;
        virtual bool isValidCoords(const Point& position) const = 0;

        virtual ICanBaseAction* getItemByCoords(const Point& position) = 0;
        virtual ICanBaseAction* getItemById(uint32_t id) = 0;

        virtual ~IBattleField() = default;
    };
}