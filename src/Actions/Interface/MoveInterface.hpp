#pragma once

#include <Actions/Interface/BaseActionInterface.hpp>

namespace sw::sim
{
    class ICanMove : virtual public ICanBaseAction
    {
    public:        
        virtual void setPosition(const Point& position) = 0;
    };
}