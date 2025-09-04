<h1 align="center">NekiraECSLib</h1>

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

NekiraECSLib 是基于 C++20 的 ECS 框架库。

## CI/CD

本项目集成了完整的持续集成和持续部署流程：

### 🔧 持续集成 (CI)

- **多平台构建**: 支持 Linux、Windows、macOS
- **多编译器支持**: GCC、Clang、MSVC
- **自动化测试**: 每次提交都会运行完整的测试套件
- **代码质量检查**: 自动检查代码格式和静态分析

### 📊 代码质量

- **格式检查**: 使用 clang-format 确保代码风格一致
- **静态分析**: 使用 clang-tidy 进行代码质量分析
- **安全扫描**: 集成 CodeQL 进行安全漏洞检测

### 🚀 自动化发布

- **版本标签**: 推送版本标签自动触发发布流程
- **构建产物**: 自动构建多平台的发布包
- **GitHub Releases**: 自动创建 GitHub 发布页面

### 📚 文档生成

- **API 文档**: 自动生成并发布 Doxygen 文档
- **文档检查**: 验证文档完整性和链接有效性

## 安装

克隆仓库至本地，使用 cmake 构建

```cmake
cmake -S . -B build -G "Ninja"
cmake --build build
cmake --install build [--prefix] [install_dir]
```

## 链接库

```cmake
find_package(NekiraECSLib REQUIRED)

target_link_libraries(YourTarget PRIVATE NekiraECSLib::NekiraECSCore)
target_include_directories(YourTarget PRIVATE ${NekiraECSLib_INCLUDE_DIRS})
```

## 文档

[![NekiraECSCore](https://img.shields.io/badge/NekiraECSCore-%2372B0FD?style=for-the-badge&labelColor=%2372B0FD&color=%2372B0FD)](/Documents/NekiraECSCore/NekiraECSCore.CN.MD)

## License

[![License](https://img.shields.io/badge/License-MIT-38E575?style=for-the-badge)](/LICENSE)
