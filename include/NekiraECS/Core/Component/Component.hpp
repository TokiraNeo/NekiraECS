/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once

#include <NekiraECS/Core/Primary/PrimaryType.hpp>
#include <algorithm>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <typeindex>
#include <vector>


namespace NekiraECS
{

// 组件接口基类
class IComponentBase
{
public:
    IComponentBase() = default;
    IComponentBase(const IComponentBase&) = default;
    IComponentBase(IComponentBase&&) noexcept = default;
    IComponentBase& operator=(const IComponentBase&) = default;
    IComponentBase& operator=(IComponentBase&&) noexcept = default;

    virtual ~IComponentBase() = default;

    virtual std::type_index GetTypeIndex() = 0;
};


// CRTP模板组件类，其他的组件类通过继承该类来实现
template <typename T>
class Component : public IComponentBase
{
    friend T;

public:
    std::type_index GetTypeIndex() override
    {
        return std::type_index(typeid(T));
    }

private:
    Component() = default;
    Component(const Component&) = default;
    Component& operator=(const Component&) = default;
    Component(Component&&) noexcept = default;
    Component& operator=(Component&&) noexcept = default;

    virtual ~Component() = default;
};

} // namespace NekiraECS


namespace NekiraECS
{

// 组件容器接口
class IComponentArrayBase
{
public:
    IComponentArrayBase() = default;
    IComponentArrayBase(const IComponentArrayBase&) = default;
    IComponentArrayBase(IComponentArrayBase&&) noexcept = default;
    IComponentArrayBase& operator=(const IComponentArrayBase&) = default;
    IComponentArrayBase& operator=(IComponentArrayBase&&) noexcept = default;

    virtual ~IComponentArrayBase() = default;

    // 容器是否为空
    [[nodiscard]] virtual bool IsEmpty() const = 0;

    // 容器大小
    [[nodiscard]] virtual size_t Size() const = 0;

    // 从特定Entity中移除该组件
    virtual void RemoveComponent(EntityIndexType entityIndex) = 0;

    // 检查特定Entity是否拥有该组件
    [[nodiscard]] virtual bool HasComponent(EntityIndexType entityIndex) = 0;

    // 清空容器
    virtual void Clear() = 0;
};


// 组件容器
template <typename T>
    requires std::is_base_of_v<Component<T>, T>
class ComponentArray final : public IComponentArrayBase
{
public:
    ComponentArray() = default;

    // 添加组件
    void AddComponent(EntityIndexType entityIndex, T component)
    {

        // 确保实体索引在ComponentIndices范围内
        if (entityIndex >= ComponentIndices.size())
        {
            ComponentIndices.resize(entityIndex + 1, INVALID_COMPONENT_INDEX);
        }

        // 如果已存在，则替换
        if (ComponentIndices[entityIndex] != INVALID_COMPONENT_INDEX)
        {
            Components[ComponentIndices[entityIndex]] = std::move(component);
            return;
        }

        /**
         * @[INFO] 添加逻辑：
         *
         * 1.当不存在该实体的组件时，即entityIndex >= ComponentIndices.size(),
         * 这时我们新扩容了ComponentIndices给entityIndex。
         *
         * 2.新的组件索引是Components的当前大小，因此我们即将添加的组件会放在Components的末尾。
         *
         * 3.我们将ComponentIndices[entityIndex]设为新的组件索引
         *
         * 4.EntityIDs与Components同步更新，因此我们直接在EntityIndices末尾添加entityIndex
         */

        // 新组件的索引是Components的当前大小
        auto compIndex = Components.size();

        // 记录该实体索引对应的组件索引
        ComponentIndices[entityIndex] = compIndex;

        // 添加组件到Components
        Components.push_back(std::move(component));

        // 记录该组件对应的实体索引
        EntityIndices.push_back(entityIndex);
    }

    // 获取组件，如果不存在则返回nullptr
    T* GetComponent(EntityIndexType entityIndex)
    {
        if (!HasComponent(entityIndex))
        {
            return nullptr;
        }

        // 获取该实体对应的组件索引
        auto compIndex = ComponentIndices[entityIndex];

        return &Components[compIndex];
    }

    // 容器是否为空
    [[nodiscard]] bool IsEmpty() const override
    {
        return Components.empty();
    }

    // 容器大小
    [[nodiscard]] size_t Size() const override
    {
        return Components.size();
    }

    // 从特定Entity中移除该组件
    void RemoveComponent(EntityIndexType entityIndex) override
    {
        if (!HasComponent(entityIndex))
        {
            return;
        }

        // 获取该实体对应的组件索引
        auto compIndex = ComponentIndices[entityIndex];

        // 获取最后一个组件的索引
        auto lastIndex = Components.size() - 1;

        /**
         * @[INFO] 删除逻辑：
         *
         * 1.我们得到了要删除的组件的索引compIndex，以及最后一个组件的索引lastIndex。
         * 2.为了保持Components的紧凑性，我们需要将最后一个组件与要删除的组件交换位置。
         * 3.最简单的方法是我们直接在compIndex上用最后一个组件覆盖它，然后删掉末尾的重复元素。
         *
         * 4.接下来是EntityIndices的更新。同上，我们用lastIndex对应的EntityIndex覆盖EntityIndices[compIndex]，
         * 然后删掉末尾的重复元素。
         *
         * 5.最后，是更新ComponentIndices。到这我们已经把最后一个组件的EntityIndex放到了EntityIndices[compIndex]位置，
         * 因此需要告知ComponentIndices，现在最后一个组件EntityIndex对应的组件索引已经变成了compIndex。
         * 最后，将ComponentIndices中的对应位置设为无效值，表示该实体不再拥有该组件。
         */

        if (compIndex != lastIndex)
        {
            Components[compIndex] = std::move(Components[lastIndex]);

            EntityIndices[compIndex] = EntityIndices[lastIndex];

            ComponentIndices[EntityIndices[compIndex]] = compIndex;
        }

        // 移除末尾的重复元素
        Components.pop_back();
        EntityIndices.pop_back();

        // 标记该实体不再拥有该组件
        ComponentIndices[entityIndex] = INVALID_COMPONENT_INDEX;
    }


    // 检查特定Entity是否拥有该组件
    [[nodiscard]] bool HasComponent(EntityIndexType entityIndex) override
    {
        return entityIndex < ComponentIndices.size() && ComponentIndices[entityIndex] != INVALID_COMPONENT_INDEX;
    }

    // 清空容器
    void Clear() override
    {
        ComponentIndices.clear();
        Components.clear();
        EntityIndices.clear();
    }

    // 回调访问所有组件
    void ForEachComponent(const std::function<void(T&)>& callback)
    {
        for (auto& comp : Components)
        {
            callback(comp);
        }
    }


private:
    // 定义无效的组件索引
    static constexpr size_t INVALID_COMPONENT_INDEX = -1;

    // 稀疏集合：每个实体索引对应的组件索引。EntityIndex -> ComponentIndex
    std::vector<size_t> ComponentIndices;

    // 紧凑集合：每个组件索引对应的组件实例。ComponentIndex -> Component
    std::vector<T> Components;

    // 紧凑集合：每个组件索引对应的实体索引。ComponentIndex -> EntityIndex
    std::vector<EntityIndexType> EntityIndices;
};

} // namespace NekiraECS
