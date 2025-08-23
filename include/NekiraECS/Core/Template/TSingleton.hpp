/**
 * MIT License
 *
 * Copyright (c) 2025 TokiraNeo (https://github.com/TokiraNeo)
 *
 * For full license information, please view the LICENSE file in the root directory of this project.
 */

#pragma once

namespace NekiraECS
{

// CRTP单例模板基类，用于快速创建单例类
template <typename T>
class TSingleton
{
    // 仅T可以访问私有部分的构造函数和析构函数，避免 Class2 ：public TSingleton<Class1> 的错误继承
    friend T;

public:
    // 获取单例实例的静态方法
    static T& Get()
    {
        static T instance;
        return instance;
    }

    // 删除拷贝构造函数和赋值操作符
    TSingleton(const TSingleton&) = delete;
    TSingleton& operator=(const TSingleton&) = delete;

    // 删除移动构造函数和赋值操作符
    TSingleton(TSingleton&&) = delete;
    TSingleton& operator=(TSingleton&&) = delete;

private:
    TSingleton() = default;
    virtual ~TSingleton() = default;
};

} // namespace NekiraECS
