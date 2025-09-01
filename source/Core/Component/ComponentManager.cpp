/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#include <Component/ComponentManager.hpp>

namespace NekiraECS
{
void ComponentManager::RemoveEntityAllComponents(EntityIndexType entityIndex)
{
    for (auto& [compType, compArray] : ComponentArrays)
    {
        compArray->RemoveComponent(entityIndex);
    }
}
} // namespace NekiraECS