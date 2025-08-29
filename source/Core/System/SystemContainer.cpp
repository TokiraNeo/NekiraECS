/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#include <System/SystemContainer.hpp>
#include <algorithm>
#include <memory>


namespace NekiraECS
{
void SystemContainer::AddSystem(std::unique_ptr<ISystemBase> system)
{
    IsSorted = false;

    // 检查系统是否存在
    for (auto& sys : Systems)
    {
        if (sys->GetTypeIndex() == system->GetTypeIndex())
        {
            sys = std::move(system);
            return;
        }
    }

    Systems.push_back(std::move(system));
}


void SystemContainer::RemoveSystem(std::type_index type)
{
    const auto EQUAL_LAMBDA = [type](const std::unique_ptr<ISystemBase>& sys) { return sys->GetTypeIndex() == type; };

    const auto IT = std::ranges::remove_if(Systems.begin(), Systems.end(), EQUAL_LAMBDA);

    Systems.erase(IT.begin(), IT.end());

    IsSorted = false;
}

ISystemBase* SystemContainer::GetSystem(std::type_index type) const
{
    const auto EQUAL_LAMBDA = [type](const std::unique_ptr<ISystemBase>& sys) { return sys->GetTypeIndex() == type; };

    const auto IT = std::ranges::find_if(Systems.begin(), Systems.end(), EQUAL_LAMBDA);

    if (IT != Systems.end())
    {
        return IT->get();
    }

    return nullptr;
}

void SystemContainer::SortingSystems()
{
    if (IsSorted)
    {
        return;
    }

    // 按优先级排序,数值越小优先级越高
    const auto SORT_LAMBDA = [](const std::unique_ptr<ISystemBase>& a, const std::unique_ptr<ISystemBase>& b)
    { return a->GetPriority() < b->GetPriority(); };

    std::ranges::sort(Systems.begin(), Systems.end(), SORT_LAMBDA);

    IsSorted = true;
}

const std::vector<std::unique_ptr<ISystemBase>>& SystemContainer::GetAllSystems() const
{
    return Systems;
}

} // namespace NekiraECS