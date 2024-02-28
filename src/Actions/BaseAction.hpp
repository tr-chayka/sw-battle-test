#pragma once

#include <Actions/Interface/BaseActionInterface.hpp>
#include <Simulator/Interface/BattleFieldInterface.hpp>

#include <memory>

namespace sw::sim
{
    class BaseAction
    {
    public:
        virtual bool execute(IBattleField* pBattleField = nullptr) = 0; // return true if succeeded
        virtual ~BaseAction() = default;
    };

    using PBaseAction = std::shared_ptr<BaseAction>;
}