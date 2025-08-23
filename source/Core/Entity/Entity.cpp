/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#include <Entity/Entity.hpp>

namespace NekiraECS
{

void EntityManager::DecodeEntity(const Entity& entity, EntityIndex_t& outIndex, EntityVersion_t& outVersion)
{
    outIndex = entity.ID >> ENTITY_INDEX_SHIFT;

    outVersion = entity.ID & ENTITY_INDEX_MASK;
}


EntityIndex_t EntityManager::GetEntityIndex(const Entity& entity)
{
    return entity.ID >> ENTITY_INDEX_SHIFT;
}


EntityIndex_t EntityManager::GetEntityIndex(EntityID_t entityID)
{
    return entityID >> ENTITY_INDEX_SHIFT;
}


EntityVersion_t EntityManager::GetEntityVersion(const Entity& entity)
{
    return entity.ID & ENTITY_INDEX_MASK;
}


EntityVersion_t EntityManager::GetEntityVersion(EntityID_t entityID)
{
    return entityID & ENTITY_INDEX_MASK;
}

bool EntityManager::IsValid(const Entity& entity) const
{
    if (entity.ID == INVALID_ENTITYID)
    {
        return false;
    }

    EntityIndex_t   index;
    EntityVersion_t version;
    DecodeEntity(entity, index, version);

    return index < EntityVersions.size() && EntityVersions[index] == version;
}


bool EntityManager::IsValid(EntityID_t entityID) const
{
    if (entityID == INVALID_ENTITYID)
    {
        return false;
    }

    EntityIndex_t   index = entityID >> ENTITY_INDEX_SHIFT;
    EntityVersion_t version = entityID & ENTITY_INDEX_MASK;

    return index < EntityVersions.size() && EntityVersions[index] == version;
}

Entity EntityManager::CreateEntity()
{
    EntityID_t id;

    // 优先使用回收的ID
    if (!RecycledIDs.empty())
    {
        id = RecycledIDs.top();
        RecycledIDs.pop();
    }
    else
    {
        // 创建新的实体索引
        auto newIndex = static_cast<EntityID_t>(EntityVersions.size());

        // 新版本号从1开始
        EntityVersion_t newVersion = 1;

        // 组合成新的实体ID
        id = (newIndex << ENTITY_INDEX_SHIFT) | newVersion;

        // 扩展版本号数组
        EntityVersions.push_back(newVersion);
    }

    return Entity(id);
}

void EntityManager::DestroyEntity(const Entity& entity)
{
    EntityIndex_t   index = entity.ID >> ENTITY_INDEX_SHIFT;
    EntityVersion_t version = entity.ID & ENTITY_INDEX_MASK;

    if (IsValid(entity.ID))
    {
        // 叠加版本号，使原先ID失效
        version += 1;
        EntityVersions[index] = version;

        // 组合新的ID并回收
        EntityID_t newID = (index << ENTITY_INDEX_SHIFT) | version;

        RecycledIDs.push(newID);
    }
}

void EntityManager::DestroyEntity(EntityID_t entityID)
{
    EntityIndex_t   index = entityID >> ENTITY_INDEX_SHIFT;
    EntityVersion_t version = entityID & ENTITY_INDEX_MASK;

    if (IsValid(entityID))
    {
        // 叠加版本号，使原先ID失效
        version += 1;
        EntityVersions[index] = version;

        // 组合新的ID并回收
        EntityID_t newID = (index << ENTITY_INDEX_SHIFT) | version;

        RecycledIDs.push(newID);
    }
}

}; // namespace NekiraECS