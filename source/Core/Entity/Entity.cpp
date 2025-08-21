/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#include "Entity/Entity.hpp"

namespace NekiraECS
{
Entity EntityManager::CreateEntity()
{
    //@[TODO] 实现EntityManager的CreateEntity方法，这里仅为示例
    return Entity(1);
}

} // namespace NekiraECS