/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#include <Entity/Entity.hpp>
#include <cstdint>


namespace NekiraECS
{

bool EntityManager::CheckEntity(const Entity& entity) const
{
    // 提取Entity的索引和版本
    uint16_t index;
    uint16_t version;
    DecodeEntity(entity.ID, index, version);

    // 检查索引是否在范围内,且版本号匹配
    return index < Versions.size() && Versions[index] == version;
}


bool EntityManager::CheckEntity(uint16_t index, uint16_t version) const
{
    // 检查索引是否在范围内,且版本号匹配
    return index < Versions.size() && Versions[index] == version;
}


Entity EntityManager::CreateEntity()
{

    // 优先使用回收的ID
    if (!RecycledIDs.empty())
    {
        // 从回收池中获取一个ID,这里的ID在回收的时候已经做了版本号递增处理，因此直接使用即可
        uint32_t NewID = RecycledIDs.top();
        RecycledIDs.pop();

        return Entity(NewID);
    }
    // 如果没有可回收的ID,则创建一个新的ID
    else
    {
        // 获取当前的Entity数量作为索引
        auto index = static_cast<uint32_t>(Versions.size());

        // 新的版本号从0开始
        uint16_t version = 0;

        // 扩展版本号池
        Versions.push_back(version);

        // 组合新的ID
        uint32_t NewID = (index << 16) | version;

        return Entity(NewID);
    }
}


void EntityManager::DestroyEntity(const Entity& entity)
{
    uint16_t index;
    uint16_t version;
    DecodeEntity(entity.ID, index, version);

    if (CheckEntity(index, version))
    {
        // 对版本号递增，确保原有的ID不再有效
        version += 1;
        // 更新版本号池
        Versions[index] = version;

        // 将ID压入回收池
        uint32_t recycledID = (static_cast<uint32_t>(index) << 16) | version;

        RecycledIDs.push(recycledID);
    }
}



void EntityManager::DecodeEntity(const Entity& entity, uint16_t& OutIndex, uint16_t& OutVersion)
{
    DecodeEntity(entity.ID, OutIndex, OutVersion);
}

void EntityManager::DecodeEntity(uint32_t ID, uint16_t& OutIndex, uint16_t& OutVersion)
{
    // ID: [Index(16 bits)][Version(16 bits)]

    OutIndex = (ID >> 16) & 0xFFFF;

    OutVersion = ID & 0xFFFF;
}

} // namespace NekiraECS