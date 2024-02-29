#pragma once

#include <Actions/MoveAction.hpp>

#include <IO/EventLogs/UnitAttacked.hpp>
#include <IO/EventLogs/UnitDied.hpp>
#include <IO/System/EventLog.hpp>

#include <cstdint>
#include <iostream>
#include <memory>

namespace sw::sim
{
    class BaseUnit : public ICanMove
    {    
    public:
        BaseUnit(uint32_t id, const Point& position, uint32_t hp) :
            unitId(id),
            unitPosition(position),
            unitHp(hp)
        {
            actionPriorityList.emplace_front(ActionType::Move);
            actionMap.emplace(ActionType::Move, std::make_shared<MoveAction>(this));
        }

        bool isKilled() const {return unitHp == 0;}
        virtual void getDamage(uint32_t damage, uint32_t from) 
        {
            if (unitHp > damage)
            {
                unitHp -= damage;
                EventLog::getLogger().log(io::UnitAttacked{
                    EventLog::getLogger().tick(), 
                    unitId, from, damage, unitHp
                });
            }
            else
            {
                unitHp = 0;

                EventLog::getLogger().log(io::UnitAttacked{
                    EventLog::getLogger().tick(),
                    unitId, from, unitHp, 0
                });

                EventLog::getLogger().log(io::UnitDied{
                    EventLog::getLogger().tick(), 
                    unitId
                });
            }
        }

        virtual Point getPosition() const { return unitPosition; }
        virtual void setPosition(const Point& position) { unitPosition = position; }

        virtual uint32_t getId() const { return unitId; }
        virtual uint32_t getHp() const { return unitHp; }

        PBaseAction getAction(ActionType action_type)
        {
            auto actionIt = actionMap.find(action_type);
            if (actionMap.end() == actionIt)
                return nullptr;

            return actionIt->second;
        }

        bool tryDoSomething(IBattleField* pBattleField)
        {
            for (auto actionType : actionPriorityList)
                if (getAction(actionType)->execute(pBattleField))
                    return true;

            return false;
        }
        
    protected:
        uint32_t unitId;
        uint32_t unitHp;
        Point unitPosition;

        std::list<ActionType> actionPriorityList;
        std::map<ActionType, PBaseAction> actionMap;
    };

    using PBaseUnit = std::shared_ptr<BaseUnit>;
}