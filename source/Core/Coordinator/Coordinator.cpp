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

bool Coordinator::CheckEntity(EntityIDType entityID)
{
    return EntityManager::Get().IsValid(entityID);
}

Entity Coordinator::CreateEntity()
{
    return EntityManager::Get().CreateEntity();
}

void Coordinator::DestroyEntity(const Entity& entity)
{
    EntityManager::Get().DestroyEntity(entity);
}

void Coordinator::DestroyEntity(EntityIDType entityID)
{
    EntityManager::Get().DestroyEntity(entityID);
}

} // namespace NekiraECS