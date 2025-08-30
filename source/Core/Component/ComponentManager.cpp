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
void ComponentManager::RemoveEntityAllComponents(const Entity& entity)
{
    if (!EntityManager::Get().IsValid(entity))
    {
        return;
    }

    auto entityIndex = EntityManager::GetEntityIndex(entity);

    for (auto& [compType, compArray] : ComponentArrays)
    {
        compArray->RemoveComponent(entityIndex);
    }
}
} // namespace NekiraECS