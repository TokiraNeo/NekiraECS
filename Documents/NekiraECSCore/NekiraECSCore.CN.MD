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

## 概述

NekiraECSCore 是核心库，主要实现了`Entity`，`Component`，`System`，`Coordinator`。命名空间为`NekiraECS::`。

## Entity

`Entity`作为 ECS 框架中的单位，只负责存储特定的 ID。在 NekiraECS 中，`Entity`的 ID 由两部分组成：`Entity`在`Entity数组`中的索引+`Entity`的版本号。可以理解为“**座位号+姓名**”。

## EntityManager

`EntityManager`负责`Entity`的生成、销毁、管理。
**通常情况下，不建议直接调用`EntityManager`，而应使用`Coordinator`进行全局调度。**

## Component

`Component`在 ECS 框架中只负责存储数据，不需要任何方法，`Component` 中应当只存在 `public` 的成员变量。

在自定义 `Component` 时，需要继承自`NekiraECS::Component<>`类。`NekiraECS::Component<>`类是一个 CRTP 的模板类，其可以为自定义的 `Component` 完成一些基本的信息收集。以下为例：

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

`ComponentManager`负责对实体的组件进行管理。其内部对某个特定类型组件的存储采用`Struct of Array(SOA)`的方式以尽可能提高在更新组件时的缓存命中率。
**通常情况下，不建议直接调用`ComponentManager`，而应使用`Coordinator`进行全局调度。**

## System

`System`主要负责特定类型组件的更新逻辑。

在自定义`System`时，需要继承自`NekiraECS::System<>`类。`NekiraECS::System<>`类是一个 CRTP 的模板类，主要为自定义的`System`做基本的类型信息收集。如下：

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

`SystemGroup`用于决定每个`System`的更新阶段，一共有六个阶段(从先至后):

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

对于每个`System`，默认的更新阶段为`SystemGroup::Update`，可以通过重写`System`中的`SystemGroup GetGroup() const`来改变分组。

### SystemPriority

对于同个分组里的`System`，又通过每个`System`自身的`SystemPriority`来决定其在组内的更新次序，`SystemPriority`的值越小，优先级越高。

对于每个`System`，默认的更新优先级为`0`，可以通过重写`System`中的`SystemPriority GetPriority() const`来改变优先级。

### 系统行为

对于系统行为，主要有三个接口可以重写：

- `void OnInitialize()`：在系统注册时调用，负责系统的初始化行为。
- `void OnDeInitialize()`：在移除系统时调用，负责系统的清理行为。
- `void OnUpdate(float deltaTime)`：在更新系统时调用，主要负责系统对组件的更新行为。

## SystemManager

`SystemManager`负责`System`的注册、移除与更新等。
**通常情况下，不建议直接调用`SystemManager`，而应使用`Coordinator`进行全局调度。**

## Coordinator

`Coordinator`负责全局的调度管理，**通常情况下，不建议绕过`Coordiantor`，这可能造成一些清理错误、标记错误等。**
