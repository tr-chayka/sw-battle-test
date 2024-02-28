#pragma once

#include <Simulator/Interface/BattleFieldInterface.hpp>
#include <Units/BaseUnit.hpp>

#include <cstdint>
#include <list>
#include <type_traits>

namespace Sim
{
    class BattleField : public IBattleField
    {
    public:
        BattleField(uint32_t w, uint32_t h) :
            battleFieldWidth(w),
            battleFieldHeight(h)
        {}

        virtual bool IsValidCoords(uint32_t x, uint32_t y) const
        {
            return x < battleFieldWidth && y < battleFieldHeight;
        }

        virtual bool IsFree(uint32_t x, uint32_t y) const
        {
            return IsValidCoords(x, y) && GetItemByCoords(x, y) == nullptr;
        }

        const ICanBaseAction* GetItemByCoords(uint32_t x, uint32_t y) const
        {
            for (auto pUnit : unitList)
                if (pUnit->GetX() == x && pUnit->GetY() == y)
                    return pUnit.get();

            return nullptr;
        }

        virtual ICanBaseAction* GetItemByCoords(uint32_t x, uint32_t y)
        {
            for (auto pUnit : unitList)
                if (pUnit->GetX() == x && pUnit->GetY() == y)
                    return pUnit.get();
            
            return nullptr;
        }

        virtual ICanBaseAction* GetItemById(uint32_t id)
        {
            return GetUnit(id).get();
        }

        template <typename T, typename ... args_t>
        void SpawnUnit(args_t ... args)
        {
            if (std::is_constructible<T, args_t ...>() && std::is_base_of<BaseUnit, T>())
                unitList.emplace_back(new T(args ...));
        }

        PBaseUnit GetUnit(uint32_t id)
        {
            for (auto pUnit : unitList)
                if (pUnit->GetId() == id)
                    return pUnit;

            return nullptr;
        }

        bool AllDied() const
        {
            return unitList.empty();
        }

        bool TryDoSomethig()
        {
            bool result = false;

            for (auto pUnit : unitList)
                result = pUnit->TryDoSomething(this) || result;

            return result;
        }

        void Clean()
        {
            auto it = std::remove_if(
                unitList.begin(),
                unitList.end(),
                [](PBaseUnit& pUnit)
                {
                    return pUnit == nullptr || pUnit->IsKilled();
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