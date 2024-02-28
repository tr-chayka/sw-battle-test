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
        virtual ~BaseAction() = default;
    };

    using PBaseAction = std::shared_ptr<BaseAction>;
}