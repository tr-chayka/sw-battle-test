#pragma once

#include <Actions/BaseAction.hpp>
#include <Actions/Interface/MoveInterface.hpp>

#include <iostream>

namespace Sim
{
    class MoveAction : public BaseAction
    {
    public:
        MoveAction(ICanMove* actor) :
            pActor(actor)
        {}

        virtual bool Execute(IBattleField* pBattleField = nullptr);
        void SetDestination(uint32_t x, uint32_t y)
        {
            destinationX = x;
            destinationY = y;
            hasDestination = true;
        }

    private:
        bool TryMoveTo(IBattleField* pBattleField, int32_t x, int32_t y);

    private:
        uint32_t destinationX {0};
        uint32_t destinationY {0};
        ICanMove* pActor {nullptr};
        bool hasDestination {false};
    };
}