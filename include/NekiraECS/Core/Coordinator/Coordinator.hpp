/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once

#include <NekiraECS/Core/Template/TSingleton.hpp>

namespace NekiraECS
{

// 协调器，负责协调实体、组件和系统
class Coordinator final : public TSingleton<Coordinator>
{};

} // namespace NekiraECS