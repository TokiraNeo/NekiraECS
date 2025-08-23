/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once

#include <NekiraECS/Core/Template/TSingleton.hpp>
#include <cstdint>
#include <stack>
#include <vector>


namespace NekiraECS
{

// 实体ID的类型定义. [Index(16 bits) | Version(16 bits)]
using EntityID_t = uint32_t;

// 定义一个无效的实体ID常量
constexpr EntityID_t INVALID_ENTITYID = 0;

// 实体索引的类型定义
using EntityIndex_t = uint16_t;

// 实体版本的类型定义
using EntityVersion_t = uint16_t;

// 定义实体ID掩码
constexpr EntityIndex_t ENTITY_INDEX_MASK = 0xFFFF;

// 定义右移位数
constexpr uint8_t ENTITY_INDEX_SHIFT = 16;

} // namespace NekiraECS



namespace NekiraECS
{

// 实体类
struct Entity final
{
    friend class EntityManager;

public:
    // 外部直接构建的为无效实体
    Entity() : ID(INVALID_ENTITYID)
    {}

private:
    // 私有构造函数，仅允许EntityManager创建实体
    explicit Entity(EntityID_t id) : ID(id)
    {}

private:
    // 实体的唯一标识符
    // 由索引和版本组成 (高16位为索引，低16位为版本)
    // [Index(16 bits) | Version(16 bits)]
    EntityID_t ID;
};

} // namespace NekiraECS



namespace NekiraECS
{

// 实体管理器单例
class EntityManager final : public TSingleton<EntityManager>
{
public:
    // 解析实体
    static void DecodeEntity(const Entity& entity, EntityIndex_t& outIndex, EntityVersion_t& outVersion);

    // 获取实体的索引
    static EntityIndex_t GetEntityIndex(const Entity& entity);
    static EntityIndex_t GetEntityIndex(EntityID_t entityID);

    // 获取实体的版本
    static EntityVersion_t GetEntityVersion(const Entity& entity);
    static EntityVersion_t GetEntityVersion(EntityID_t entityID);

    // 实体是否有效
    bool IsValid(const Entity& entity) const;
    bool IsValid(EntityID_t entityID) const;

    // 创建一个新实体
    Entity CreateEntity();

    // 销毁一个实体
    void DestroyEntity(const Entity& entity);
    void DestroyEntity(EntityID_t entityID);

private:
    // 每个实体的版本号 EntityIndex -> EntityVersion
    std::vector<EntityVersion_t> EntityVersions;

    // 可复用的实体ID.版本号在回收时已做+1处理，因此可以直接复用
    std::stack<EntityID_t> RecycledIDs;
};

} // namespace NekiraECS