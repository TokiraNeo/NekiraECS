/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once


#include <NekiraECS/Core/Component/ComponentManager.hpp>
#include <NekiraECS/Core/System/SystemManager.hpp>



namespace NekiraECS
{

// 协调器，负责协调实体、组件和系统
class Coordinator final : public TSingleton<Coordinator>
{
public:
    // ===============================
    // Entity Management
    // ===============================

    // 实体是否有效
    static bool CheckEntity(const Entity& entity);
    static bool CheckEntity(EntityIDType entityID);

    // 创建实体
    static Entity CreateEntity();

    // 销毁实体
    static void DestroyEntity(const Entity& entity);
    static void DestroyEntity(EntityIDType entityID);


    // ===============================
    // Component Management
    // ===============================

    // 添加组件
    template <typename T, typename... Args>
        requires std::is_base_of_v<Component<T>, T>
    static void AddComponent(const Entity& entity, Args&&... args)
    {
        ComponentManager::Get().AddComponent<T>(entity, std::forward<Args>(args)...);
    }

    // 获取组件，如果不存在或实体无效则返回nullptr
    template <typename T>
        requires std::is_base_of_v<Component<T>, T>
    static T* GetComponent(const Entity& entity)
    {
        return ComponentManager::Get().GetComponent<T>(entity);
    }

    // 是否拥有该组件
    template <typename T>
        requires std::is_base_of_v<Component<T>, T>
    static bool HasComponent(const Entity& entity)
    {
        return ComponentManager::Get().HasComponent<T>(entity);
    }

    // 移除组件
    template <typename T>
        requires std::is_base_of_v<Component<T>, T>
    static void RemoveComponent(const Entity& entity)
    {
        ComponentManager::Get().RemoveComponent<T>(entity);
    }


    // ===============================
    // System Management
    // ===============================

    // 注册系统
    template <typename T, typename... Args>
        requires std::is_base_of_v<System<T>, T>
    static T* RegisterSystem(Args&&... args)
    {
        return SystemManager::Get().RegisterSystem<T>(std::forward<Args>(args)...);
    }

    // 是否存在某个系统
    template <typename T>
        requires std::is_base_of_v<System<T>, T>
    static bool HasSystem()
    {
        return SystemManager::Get().HasSystem<T>();
    }

    // 移除某个系统
    template <typename T>
        requires std::is_base_of_v<System<T>, T>
    static void RemoveSystem()
    {
        SystemManager::Get().RemoveSystem<T>();
    }

private:
};

} // namespace NekiraECS