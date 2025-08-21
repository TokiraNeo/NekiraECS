/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once


#include <atomic>
#include <cstdint>


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

    // 设置允许的最大Entity数量
    void SetMaxEntityCount(uint32_t count)
    {
        MaxEntityCount.store(count);
    }


    // 创建一个新的Entity实例
    Entity CreateEntity();

private:
    EntityManager() = default;

    // 允许的最大Entity数量，默认值为1000
    std::atomic<uint32_t> MaxEntityCount{1000};

    // 上一次创建的Entity ID
    std::atomic<uint32_t> LastEntityID{0};
};

} // namespace NekiraECS