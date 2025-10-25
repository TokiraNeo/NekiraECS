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

EntityManager& EntityManager::Get()
{
    static EntityManager instance;
    return instance;
}

void EntityManager::DecodeEntity(const Entity& entity, EntityIndexType& outIndex, EntityVersionType& outVersion)
{
    //@[INFO] C++的右移运算符对于无符号整数是逻辑右移，对于有符号整数是算术右移
    // 这里的ID是无符号整数类型，所以右移时高位补0，这保证了右移后仍能得到正确的索引值
    outIndex = entity.ID >> ENTITY_INDEX_SHIFT;

    outVersion = entity.ID & ENTITY_VERSION_MASK;
}


EntityIndexType EntityManager::GetEntityIndex(const Entity& entity)
{
    return entity.ID >> ENTITY_INDEX_SHIFT;
}


EntityIndexType EntityManager::GetEntityIndex(EntityIDType entityID)
{
    return entityID >> ENTITY_INDEX_SHIFT;
}


EntityVersionType EntityManager::GetEntityVersion(const Entity& entity)
{
    return entity.ID & ENTITY_VERSION_MASK;
}


EntityVersionType EntityManager::GetEntityVersion(EntityIDType entityID)
{
    return entityID & ENTITY_VERSION_MASK;
}

bool EntityManager::IsValid(const Entity& entity) const
{
    if (entity.ID == INVALID_ENTITYID)
    {
        return false;
    }

    EntityIndexType   index{};
    EntityVersionType version{};
    DecodeEntity(entity, index, version);

    return index < EntityVersions.size() && EntityVersions[index] == version;
}


bool EntityManager::IsValid(EntityIDType entityID) const
{
    if (entityID == INVALID_ENTITYID)
    {
        return false;
    }

    EntityIndexType   index = entityID >> ENTITY_INDEX_SHIFT;
    EntityVersionType version = entityID & ENTITY_VERSION_MASK;

    return index < EntityVersions.size() && EntityVersions[index] == version;
}

Entity EntityManager::CreateEntity()
{
    EntityIDType id{};

    // 优先使用回收的ID
    if (!RecycledIDs.empty())
    {
        id = RecycledIDs.top();
        RecycledIDs.pop();
    }
    else
    {
        // 创建新的实体索引
        auto newIndex = static_cast<EntityIDType>(EntityVersions.size());

        // 新版本号从1开始
        EntityVersionType newVersion = 1;

        // 组合成新的实体ID
        id = (newIndex << ENTITY_INDEX_SHIFT) | newVersion;

        // 扩展版本号数组
        EntityVersions.push_back(newVersion);
    }

    return Entity(id);
}

void EntityManager::DestroyEntity(const Entity& entity)
{
    EntityIndexType   index = entity.ID >> ENTITY_INDEX_SHIFT;
    EntityVersionType version = entity.ID & ENTITY_VERSION_MASK;

    if (IsValid(entity.ID))
    {
        // 叠加版本号，使原先ID失效
        version += 1;
        EntityVersions[index] = version;

        // 组合新的ID并回收
        EntityIDType newID = (static_cast<EntityIDType>(index) << ENTITY_INDEX_SHIFT) | version;

        RecycledIDs.push(newID);
    }
}


std::vector<Entity> EntityManager::GetAllEntities() const
{
    std::vector<Entity> entities;

    for (size_t index = 0; index < EntityVersions.size(); ++index)
    {
        EntityVersionType version = EntityVersions[index];

        EntityIDType id = (static_cast<EntityIDType>(index) << ENTITY_INDEX_SHIFT) | version;

        if (IsValid(id))
        {
            entities.push_back(Entity(id));
        }
    }

    return entities;
}

void EntityManager::ForEachEntity(const std::function<void(const Entity&)>& callback) const
{
    for (size_t index = 0; index < EntityVersions.size(); ++index)
    {
        EntityVersionType version = EntityVersions[index];

        EntityIDType id = (static_cast<EntityIDType>(index) << ENTITY_INDEX_SHIFT) | version;

        if (IsValid(id))
        {
            callback(Entity(id));
        }
    }
}
}; // namespace NekiraECS