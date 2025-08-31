/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once

#include <cstdint>

namespace NekiraECS
{

// 实体ID的类型定义. [Index(16 bits) | Version(16 bits)]
using EntityIDType = uint32_t;

// 定义一个无效的实体ID常量
constexpr EntityIDType INVALID_ENTITYID = 0;

// 实体索引的类型定义
using EntityIndexType = uint16_t;

// 实体版本的类型定义
using EntityVersionType = uint16_t;

// 定义实体ID掩码
constexpr EntityIndexType ENTITY_INDEX_MASK = 0xFFFF;

// 定义右移位数
constexpr uint8_t ENTITY_INDEX_SHIFT = 16;

} // namespace NekiraECS