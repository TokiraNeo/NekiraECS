/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once

#include <typeindex>

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
    virtual std::type_index GetTypeIndex() = 0;

    // 初始化系统,系统注册时调用
    virtual void OnInitialize() = 0;

    /**
     * @[INFO] 系统执行周期
     * 系统的每次执行周期分为三个阶段：OnBegin -> OnExecute -> OnEnd
     * 通过重写OnBegin()，OnExecute()，OnEnd()分别定义系统在对应阶段的行为
     */

    // 系统开始执行
    virtual void OnBegin() = 0;

    // 系统执行期间
    virtual void OnExecute() = 0;

    // 系统执行结束
    virtual void OnEnd() = 0;
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
    std::type_index GetTypeIndex() override
    {
        return std::type_index(typeid(T));
    }

    // 初始化系统,系统注册时调用
    virtual void OnInitialize() override
    {
        // @[INFO] Override this in child.
    }

    // 系统开始执行
    virtual void OnBegin() override
    {
        // @[INFO] Override this in child.
    }

    // 系统执行期间
    virtual void OnExecute() override
    {
        // @[INFO] Override this in child.
    }

    // 系统执行结束
    virtual void OnEnd() override
    {
        // @[INFO] Override this in child.
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