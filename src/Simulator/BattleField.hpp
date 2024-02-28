#pragma once

#include <Simulator/Interface/BattleFieldInterface.hpp>
#include <Units/BaseUnit.hpp>

#include <cstdint>
#include <list>
#include <type_traits>

namespace sw::sim
{
    class BattleField : public IBattleField
    {
    public:
        BattleField(uint32_t w, uint32_t h) :
            battleFieldWidth(w),
            battleFieldHeight(h)
        {}

        virtual bool isValidCoords(const Point& position) const
        {
            return position.x < battleFieldWidth && position.y < battleFieldHeight;
        }

        virtual bool isFree(const Point& position) const
        {
            return isValidCoords(position) && getItemByCoords(position) == nullptr;
        }

        const ICanBaseAction* getItemByCoords(const Point& position) const
        {
            for (auto pUnit : unitList)
                if (pUnit->getPosition() == position)
                    return pUnit.get();

            return nullptr;
        }

        virtual ICanBaseAction* getItemByCoords(const Point& position)
        {
            for (auto pUnit : unitList)
                if (pUnit->getPosition() == position)
                    return pUnit.get();
            
            return nullptr;
        }

        virtual ICanBaseAction* getItemById(uint32_t id)
        {
            return getUnit(id).get();
        }

        template <typename T, typename ... args_t>
        void spawnUnit(args_t ... args)
        {
            if (std::is_constructible<T, args_t ...>() && std::is_base_of<BaseUnit, T>())
                unitList.emplace_back(new T(args ...));
        }

        PBaseUnit getUnit(uint32_t id)
        {
            for (auto pUnit : unitList)
                if (pUnit->getId() == id)
                    return pUnit;

            return nullptr;
        }

        bool allDied() const // :(
        {
            return unitList.empty();
        }

        bool tryDoSomethig()
        {
            bool result = false;

            for (auto pUnit : unitList)
                result = pUnit->tryDoSomething(this) || result;

            return result;
        }

        void clean()
        {
            auto it = std::remove_if(
                unitList.begin(),
                unitList.end(),
                [](PBaseUnit& pUnit)
                {
                    return pUnit == nullptr || pUnit->isKilled();
                }
            );

            unitList.erase(it, unitList.end());
        }

    private:
        uint32_t battleFieldWidth;
        uint32_t battleFieldHeight;
        std::list<PBaseUnit> unitList;
    };
}