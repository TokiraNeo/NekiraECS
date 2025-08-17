# ==============================================
# Root
# ==============================================

cmake_minimum_required(VERSION 3.20)
Project(NekiraECSLib LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加子目录
add_subdirectory(Modules)

# 总目标
add_custom_target(NekiraECSLib)