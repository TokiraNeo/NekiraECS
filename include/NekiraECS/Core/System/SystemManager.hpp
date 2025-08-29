/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once

#include "System.hpp"
#include "System/SystemContainer.hpp"
#include <NekiraECS/Core/System/SystemContainer.hpp>
#include <NekiraECS/Core/Template/TSingleton.hpp>

#include <typeindex>
#include <unordered_map>



namespace NekiraECS
{

// 系统管理器
class SystemManager final : public TSingleton<SystemManager>
{
private:
    // 系统分组映射
    std::unordered_map<SystemGroup, SystemContainerHandle> SystemGroups;

    // 需要重新排序的分组
    std::vector<SystemGroup> DirtyGroups;

    // 标记分组为脏，需要重新排序
    void MarkGroupDirty(SystemGroup group);

    // 对脏分组进行重新排序
    void SortSystemGroups();

    // 更新所有系统
    void UpdateSystemGroups(float deltaTime);

public:
    // 更新所有系统
    void Update(float deltaTime);

    // 注册系统
    template <typename T, typename... Args>
        requires std::is_base_of_v<System<T>, T>
    T* RegisterSystem(Args&&... args)
    {
        auto system = std::make_unique<T>(std::forward<Args>(args)...);
        T*   systemPtr = system.get();

        SystemGroup group = system->GetGroup();
        SystemGroups[group]->AddSystem(std::move(system));

        // 标记该分组需要重新排序
        MarkGroupDirty(group);

        return systemPtr;
    }

    // 是否存在某个系统
    template <typename T>
        requires std::is_base_of_v<System<T>, T>
    bool HasSystem()
    {
        SystemGroup group = T().GetGroup();
        auto        type = std::type_index(typeid(T));

        return SystemGroups.contains(group) && SystemGroups[group]->GetSystem(type) != nullptr;
    }

    // 移除某个系统
    template <typename T>
        requires std::is_base_of_v<System<T>, T>
    void RemoveSystem()
    {
        SystemGroup group = T().GetGroup();

        auto type = std::type_index(typeid(T));

        if (!SystemGroups.contains(group))
        {
            return;
        }

        if (auto* system = SystemGroups[group]->GetSystem(type))
        {
            // 反初始化系统
            system->OnDeInitialize();

            SystemGroups[group]->RemoveSystem(type);

            // 标记该分组需要重新排序
            MarkGroupDirty(group);
        }
    }
};

} // namespace NekiraECS