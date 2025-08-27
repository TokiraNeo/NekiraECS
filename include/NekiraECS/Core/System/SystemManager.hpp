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
#include <unordered_map>
#include <unordered_set>


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
private:
    // 每个分组的系统列表
    std::unordered_map<SystemGroup, std::unique_ptr<SystemInfo>> SystemMap;

    // 每个分组是否需要重新排序
    std::unordered_map<SystemGroup, bool> NeedSortingMap;

    // 对指定阶段的系统进行排序，考虑优先级和依赖关系
    void SortSystemsInGroup(SystemGroup group);

    // 检查指定阶段的系统是否存在循环依赖
    [[nodiscard]] bool HasCircularDependency(SystemGroup group) const;

    // 深度优先搜索辅助函数，用于检测循环依赖
    bool DFSCircularCheck(const std::string&                                               systemName,
                          const std::unordered_map<std::string, std::vector<std::string>>& dependencyGraph,
                          std::unordered_set<std::string>&                                 visited,
                          const std::unordered_set<std::string>&                           recursionStack) const;

public:
};


} // namespace NekiraECS