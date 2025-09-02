/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#include <System/SystemManager.hpp>
#include <algorithm>

namespace NekiraECS
{
SystemManager& SystemManager::Get()
{
    static SystemManager instance;
    return instance;
}


void SystemManager::MarkGroupDirty(SystemGroup group)
{
    auto it = std::ranges::find(DirtyGroups, group);
    if (it == DirtyGroups.end())
    {
        DirtyGroups.push_back(group);
    }
}


void SystemManager::SortSystemGroups()
{
    for (auto group : DirtyGroups)
    {
        SystemGroups[group]->SortingSystems();
    }

    DirtyGroups.clear();
}


void SystemManager::UpdateSystemGroups(float deltaTime)
{
    //@[TODO] 这里可以考虑多线程更新不同分组的系统

    for (auto group : SYSTEM_GROUPS)
    {
        if (!SystemGroups.contains(group))
        {
            continue;
        }

        for (const auto& system : SystemGroups[group]->GetAllSystems())
        {
            system->OnUpdate(deltaTime);
        }
    }
}


void SystemManager::Update(float deltaTime)
{
    // 先对脏分组进行排序
    SortSystemGroups();

    // 更新所有系统
    UpdateSystemGroups(deltaTime);
}
} // namespace NekiraECS