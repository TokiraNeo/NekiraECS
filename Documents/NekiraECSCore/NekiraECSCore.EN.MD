<h1 align="center">NekiraECSCore</h1>

![GitHub License](https://img.shields.io/github/license/TokiraNeo/NekiraECS?style=flat-square&color=%233effc2)
![GitHub top language](https://img.shields.io/github/languages/top/TokiraNeo/NekiraECS?style=flat-square&color=%23f25037)
![C++ Std](https://img.shields.io/badge/C%2B%2B_std-%3E%3D20-%23F761AE?style=flat-square)
![CMake Version](https://img.shields.io/badge/CMake-%3E%3D3.20-%2366F59F?style=flat-square)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/TokiraNeo/NekiraECS?style=flat-square&labelColor=91CBED&color=A0AEDE)

<!-- CI/CD Status Badges -->

![CI](https://img.shields.io/github/actions/workflow/status/TokiraNeo/NekiraECS/ci.yml?branch=main&style=flat-square&label=CI&color=%2300d4aa)
![Code Quality](https://img.shields.io/github/actions/workflow/status/TokiraNeo/NekiraECS/code-quality.yml?branch=main&style=flat-square&label=Code%20Quality&color=%23ff6b6b)
![Documentation](https://img.shields.io/github/actions/workflow/status/TokiraNeo/NekiraECS/documentation.yml?branch=main&style=flat-square&label=Docs&color=%234ecdc4)
![Release](https://img.shields.io/github/v/release/TokiraNeo/NekiraECS?style=flat-square&color=%23f7b801)

[![README CN](https://img.shields.io/badge/README-%E4%B8%AD%E6%96%87-%2331EDA8?style=for-the-badge)](/Documents/README/README.CN.MD)
[![README EN](https://img.shields.io/badge/README-EN-%2331D4ED?style=for-the-badge)](/Documents/README/README.EN.MD)

## Overview

NekiraECSCore is the core library, primarily implementing `Entity`, `Component`, `System`, and `Coordinator`. The namespace used is `NekiraECS::`.

## Entity

An `Entity` acts as a unit within the ECS framework, responsible solely for storing a specific ID.
In NekiraECS, an Entity's ID consists of two parts: the index within the Entity array and the version number of the Entity. It can be understood as "**Seat Number + Name**".

## EntityManager

The `EntityManager` is responsible for creating, destroying, and managing Entity instances.

**Usually, direct calls to `EntityManager` are discouraged; instead, use the `Coordinator` for global management.**

## Component

In the ECS framework, `Components `are solely responsible for storing data and do not require any methods. All `Components` should have only `public member variables`.

When creating custom `Components`, they need to inherit from `NekiraECS::Component<>`. The class `NekiraECS::Component<>` is a CRTP (Curiously Recurring Template Pattern) template that facilitates basic information collection for custom components. An example is as follows:

```c++
#include <NekiraECS/Core/Component/Component.hpp>

class HealthComponent : public NekiraECS::Component<HealthComponent>
{
public:
    float Health{0.0F};
};

class ArmorComponent : public NekiraECS::Component<ArmorComponent>
{
public:
    float Armor{0.0F};
};
```

## ComponentManager

The `ComponentManager` manages the components of entities. Internally, it employs a `Struct of Arrays (SoA)` structure for storing specific component types to optimize cache efficiency during updates.

**Usually, direct interaction with `ComponentManager` is discouraged; instead, use the `Coordinator` for global coordination.**

## System

The `System` is responsible for updating logic associated with specific component types.

When creating custom `Systems`, they should inherit from `NekiraECS::System<>`. The class `NekiraECS::System<>` is also a CRTP template that provides basic type information collection for custom systems. Examples:

```c++
#include <NekiraECS/Core/System/System.hpp>

class HealthSystem : public NekiraECS::System<HealthSystem>
{

};

class ArmorSystem : public NekiraECS::System<ArmorSystem>
{

};
```

### SystemGroup

`SystemGroup` determines the update phase for each System. There are six phases (in sequence):

```c++
enum class SystemGroup : uint8_t
{
    BeginFrame = 0,
    PreUpdate,
    Update,
    PostUpdate,
    Presentation,
    EndFrame
};
```

By default, each System is assigned to the `SystemGroup::Update` phase. This can be altered by overriding the `SystemGroup GetGroup() const` method in the `System`.

### SystemPriority

Within the same phase, the execution order of Systems is determined by their `SystemPriority`. **A lower SystemPriority value means higher priority.**

Each System has a default priority of `0`. To change this, override the `SystemPriority GetPriority() const` method.

### System Behavior

Key interface functions that can be overridden:

- `void OnInitialize()` — Called when the system is registered; used for initialization.
- `void OnDeInitialize()` — Called when the system is removed; used for cleanup.
- `void OnUpdate(float deltaTime)` — Called during each update cycle; handles the system's component updates.

## SystemManager

The `SystemManager` oversees registering, removing, and updating systems.

**Usually, direct interactions with `SystemManager` are discouraged; instead, use the `Coordinator`.**

## Coordinator

The `Coordinator` manages global scheduling.

**In general, it is recommended to avoid bypassing the `Coordinator` to prevent potential issues like cleanup errors or incorrect state management.**
