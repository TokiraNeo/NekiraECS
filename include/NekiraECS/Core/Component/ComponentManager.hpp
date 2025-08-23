/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once

#include <NekiraECS/Core/Component/Component.hpp>
#include <memory>
#include <unordered_map>


namespace NekiraECS
{
// 组件管理器
class ComponentManager : public TSingleton<ComponentManager>
{
public:
private:
    // 每种组件类型对应的组件数组
    std::unordered_map<std::type_index, std::unique_ptr<IComponentArrayBase>> ComponentArrays;
};
} // namespace NekiraECS