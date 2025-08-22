/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once


#include <cstdint>
#include <stack>
#include <vector>



namespace NekiraECS
{

struct Entity final
{
    // 友元类EntityManager，只能由EntityManager创建和管理Entity实例
    friend class EntityManager;

public:
    // 禁止拷贝和移动构造函数
    Entity(const Entity&) = delete;
    Entity(Entity&&) = delete;

    // 禁止拷贝和移动赋值操作符
    Entity& operator=(const Entity&) = delete;
    Entity& operator=(Entity&&) = delete;

    // 比较操作符
    bool operator==(const Entity& other) const
    {
        return ID == other.ID;
    }

    bool operator!=(const Entity& other) const
    {
        return !(*this == other);
    }

private:
    // 私有化构造函数，确保Entity无法被外部直接实例化，只能通过EntityManager创建
    // 这也确保了每个Entity的ID是唯一且受控的

    Entity() = default;

    explicit Entity(uint32_t id) : ID(id)
    {}

private:
    // Entity的唯一标识符,由两部分组成：
    // - 高16位：表示Entity的索引
    // - 低16位：表示Entity的版本
    // ID: [Index(16 bits)][Version(16 bits)]
    uint32_t ID;
};


class EntityManager final
{
public:
    // 禁止拷贝和移动构造函数
    EntityManager(const EntityManager&) = delete;
    EntityManager(EntityManager&&) = delete;

    // 禁止拷贝和移动赋值操作符
    EntityManager& operator=(const EntityManager&) = delete;
    EntityManager& operator=(EntityManager&&) = delete;

    // 获取单例实例
    static EntityManager& Get()
    {
        static EntityManager instance;
        return instance;
    }

    // 判断Entity是否有效
    bool CheckEntity(const Entity& entity) const;
    bool CheckEntity(uint16_t index, uint16_t version) const;

    // 创建一个新的Entity实例
    Entity CreateEntity();

    // 销毁一个Entity实例
    void DestroyEntity(const Entity& entity);

private:
    EntityManager() = default;

    // 获取Entity的索引与版本号
    static void DecodeEntityID(uint32_t ID, uint16_t& OutIndex, uint16_t& OutVersion);

    // 存储每个Entity索引对应的版本号
    std::vector<uint16_t> Versions;

    // 存储可重用的Entity ID(Index+Version),
    // 回收池里的ID在回收时已经做了版本号递增处理，因此可以直接使用
    std::stack<uint32_t> RecycledIDs;
};

} // namespace NekiraECS