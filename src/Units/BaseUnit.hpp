#pragma once

#include <Actions/MoveAction.hpp>

#include <cstdint>
#include <iostream>
#include <memory>

namespace Sim
{
    class BaseUnit : public ICanMove
    {    
    public:
        BaseUnit(uint32_t id, uint32_t x, uint32_t y, uint32_t hp) :
            Id(id),
            X(x),
            Y(y),
            Hp(hp)
        {
            actionPriorityList.emplace_front(ActionType::Move);
            actionMap.emplace(ActionType::Move, std::make_shared<MoveAction>(this));
        }

        bool IsKilled() const {return Hp == 0;}
        virtual void GetDamage(uint32_t damage) {Hp = (Hp > damage) ? (Hp - damage) : 0;}

        virtual uint32_t GetX() const { return X; }
        virtual uint32_t GetY() const { return Y; }
        virtual void SetX(uint32_t x) { X = x; }
        virtual void SetY(uint32_t y) { Y = y; }

        virtual uint32_t GetId() const { return Id; }
        virtual uint32_t GetHp() const { return Hp; }

        PBaseAction GetAction(ActionType action_type)
        {
            auto actionIt = actionMap.find(action_type);

            if (actionMap.end() != actionIt)
                return actionIt->second;
            else
                return nullptr;
        }

        bool TryDoSomething(IBattleField* pBattleField)
        {
            for (auto actionType : actionPriorityList)
                if (GetAction(actionType)->Execute(pBattleField))
                    return true;

            return false;
        }
        
    protected:
        uint32_t Id;
        uint32_t Hp;
        uint32_t X;
        uint32_t Y;

        std::list<ActionType> actionPriorityList;
        std::map<ActionType, PBaseAction> actionMap;
    };

    using PBaseUnit = std::shared_ptr<BaseUnit>;
}