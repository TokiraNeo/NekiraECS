/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once

#include <NekiraECS/Core/System/System.hpp>
#include <NekiraECS/Core/Template/TSingleton.hpp>
#include <memory>


namespace NekiraECS
{

// 系统信息
struct SystemInfo
{
    SystemInfo() : SystemInstance(nullptr), Priority(SYSTEM_PRIORITY_DEFAULT), Dependencies({})
    {}

    SystemInfo(std::unique_ptr<ISystemBase> system)
        : SystemInstance(std::move(system)), Group(SystemInstance->GetGroup()), Priority(SystemInstance->GetPriority()),
          Dependencies(SystemInstance->GetDependencies())
    {}

    bool                         IsInitialized = false;
    std::unique_ptr<ISystemBase> SystemInstance;
    SystemGroup                  Group = SystemGroup::Update;
    SystemPriority               Priority;
    std::vector<std::string>     Dependencies;
};

} // namespace NekiraECS


namespace NekiraECS
{

// 系统管理器
class SystemManager final : public TSingleton<SystemManager>
{
public:
private:
};

} // namespace NekiraECS