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

Coordinator& Coordinator::Get()
{
    static Coordinator instance;
    return instance;
}

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
    if (CheckEntity(entity))
    {
        // 移除实体的所有组件
        ComponentManager::Get().RemoveEntityAllComponents(EntityManager::GetEntityIndex(entity));

        EntityManager::Get().DestroyEntity(entity);
    }
}

void Coordinator::ForEachEntity(const std::function<void(const Entity&)>& callback)
{
    EntityManager::Get().ForEachEntity(callback);
}

void Coordinator::RemoveEntityAllComponents(const Entity& entity)
{
    if (CheckEntity(entity))
    {
        auto entityIndex = EntityManager::GetEntityIndex(entity);
        ComponentManager::Get().RemoveEntityAllComponents(entityIndex);
    }
}

void Coordinator::UpdateSystems(float deltaTime)
{
    SystemManager::Get().Update(deltaTime);
}

} // namespace NekiraECS