#pragma once

#include <Actions/BaseAction.hpp>
#include <Actions/Interface/MoveInterface.hpp>

namespace sw::sim
{
    class MoveAction : public BaseAction
    {
    public:
        MoveAction(ICanMove* actor) :
            pActor(actor)
        {}

        virtual bool execute(IBattleField* pBattleField = nullptr);
        void setDestination(const Point& destination)
        {
            destinationPoint = destination;
            hasDestination = true;
        }

    private:
        bool tryMoveTo(IBattleField* pBattleField, const Point& position);

    private:
        Point destinationPoint{ 0, 0 };
        ICanMove* pActor{ nullptr };
        bool hasDestination{ false };
    };
}