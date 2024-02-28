#pragma once

#include <Actions/Interface/BaseActionInterface.hpp>

namespace Sim
{
    class ICanMove : virtual public ICanBaseAction
    {
    public:        
        virtual void SetX(uint32_t) = 0;
        virtual void SetY(uint32_t) = 0;
    };
}