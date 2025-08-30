/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */


#include <Coordinator/Coordinator.hpp>



namespace NekiraECS
{

bool Coordinator::CheckEntity(const Entity& entity)
{
    return EntityManager::Get().IsValid(entity);
}


Entity Coordinator::CreateEntity()
{
    return EntityManager::Get().CreateEntity();
}

void Coordinator::DestroyEntity(const Entity& entity)
{
    // 移除实体的所有组件
    ComponentManager::Get().RemoveEntityAllComponents(entity);

    EntityManager::Get().DestroyEntity(entity);
}

void Coordinator::ForEachEntity(const std::function<void(const Entity&)>& callback)
{
    EntityManager::Get().ForEachEntity(callback);
}

void Coordinator::RemoveEntityAllComponents(const Entity& entity)
{
    ComponentManager::Get().RemoveEntityAllComponents(entity);
}


} // namespace NekiraECS