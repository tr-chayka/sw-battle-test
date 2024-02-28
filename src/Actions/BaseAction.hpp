#pragma once

#include <Actions/Interface/BaseActionInterface.hpp>
#include <Simulator/Interface/BattleFieldInterface.hpp>

#include <memory>

namespace Sim
{
    class BaseAction
    {
    public:
        virtual bool Execute(IBattleField* pBattleField = nullptr) = 0; // return true if succeeded
    };

    using PBaseAction = std::shared_ptr<BaseAction>;
}