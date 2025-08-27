/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once

#include <cstdint>
#include <string>
#include <typeindex>
#include <vector>


namespace NekiraECS
{

// 系统优先级，数值越小优先级越高
using SystemPriority = int32_t;

// 默认系统优先级
constexpr SystemPriority SYSTEM_PRIORITY_DEFAULT = 0;

// 系统执行阶段分组
enum class SystemGroup : uint8_t
{
    PreUpdate = 0, // 预更新阶段
    Update,        // 更新阶段
    PostUpdate,    // 更新后阶段
    Render,        // 渲染阶段
    Cleanup        // 清理阶段
};

} // namespace NekiraECS


namespace NekiraECS
{
// 系统基础接口
class ISystemBase
{
public:
    ISystemBase() = default;
    ISystemBase(const ISystemBase&) = default;
    ISystemBase(ISystemBase&&) noexcept = default;
    ISystemBase& operator=(const ISystemBase&) = default;
    ISystemBase& operator=(ISystemBase&&) noexcept = default;

    virtual ~ISystemBase() = default;

    // 获取系统类型
    [[nodiscard]] virtual std::type_index GetTypeIndex() const = 0;

    // 获取系统名
    [[nodiscard]] virtual std::string GetName() const = 0;

    // 获取系统分组
    [[nodiscard]] virtual SystemGroup GetGroup() const = 0;

    // 获取系统优先级
    [[nodiscard]] virtual SystemPriority GetPriority() const = 0;

    // 获取系统依赖的其他系统名称列表
    [[nodiscard]] virtual std::vector<std::string> GetDependencies() const = 0;

    // 初始化系统,系统注册时调用
    virtual void OnInitialize() = 0;

    // 系统更新
    virtual void OnUpdate(float deltaTime) = 0;

    // 系统清理
    virtual void OnCleanup() = 0;

    // 系统是否激活
    [[nodiscard]] bool IsSystemActive() const
    {
        return IsActive;
    }

    // 设置系统激活状态
    void SetSystemActive(bool active)
    {
        IsActive = active;
    }

private:
    // 系统是否激活,默认激活
    bool IsActive = true;
};


} // namespace NekiraECS


namespace NekiraECS
{
// CRTP模板系统类，其他系统需要继承此类
template <typename T>
class System : public ISystemBase
{
    friend T;

public:
    // 获取系统类型
    [[nodiscard]] std::type_index GetTypeIndex() const override
    {
        return std::type_index(typeid(T));
    }

    // 获取系统名字
    [[nodiscard]] std::string GetName() const override
    {
        return typeid(T).name();
    }

    // 获取系统分组，默认为Update
    [[nodiscard]] SystemGroup GetGroup() const override
    {
        return SystemGroup::Update;
    }

    // 获取系统优先级，默认为0
    [[nodiscard]] SystemPriority GetPriority() const override
    {
        return SYSTEM_PRIORITY_DEFAULT;
    }

    // 获取系统依赖的其他系统名称列表，默认为空
    [[nodiscard]] std::vector<std::string> GetDependencies() const override
    {
        return {};
    }

private:
    System() = default;
    System(const System&) = default;
    System& operator=(const System&) = default;
    System(System&&) noexcept = default;
    System& operator=(System&&) noexcept = default;

    virtual ~System() = default;
};
} // namespace NekiraECS
