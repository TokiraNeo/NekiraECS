# ==============================================
# Root
# ==============================================

cmake_minimum_required(VERSION 3.20)
Project(NekiraECSLib LANGUAGES CXX VERSION 1.0.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 导入必要的模块
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# 添加子目录
add_subdirectory(include/NekiraECS)

# ==============================================
# 总目标
# ==============================================

# 定义包含的模块
set(Module_Targets NekiraECSCore)

# 收集所有模块目标
set(NekiraECSLib_Modules)
foreach(SingleModule ${Module_Targets})
    list(APPEND NekiraECSLib_Modules ${SingleModule})
endforeach()

# 总目标
add_custom_target(NekiraECSLib)
# 令总目标依赖于所有模块目标
add_dependencies(NekiraECSLib ${NekiraECSLib_Modules})

# ==============================================
# 安装设置
# ==============================================

# config文件的路径
set(CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/NekiraECSLib)

# 创建版本配置文件
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraECSLibConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# 指定要安装的目标
install(TARGETS ${NekiraECSLib_Modules}
    EXPORT NekiraECSLibTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# 指定NekiraECSLib的Targets.cmake文件
install(EXPORT NekiraECSLibTargets
    FILE NekiraECSLibTargets.cmake
    NAMESPACE NekiraECSLib::
    DESTINATION ${CONFIG_INSTALL_DIR}
)

# 配置NekiraECSLib的Config.cmake文件
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/NekiraECSLibConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraECSLibConfig.cmake"
    INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)

# 安装配置文件
install(FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraECSLibConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/NekiraECSLibConfigVersion.cmake"
    DESTINATION ${CONFIG_INSTALL_DIR}
)

# ==============================================
# 导出
# ==============================================

# 导出NekiraECSLib的Targets.cmake文件
export(EXPORT NekiraECSLibTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/NekiraECSLibTargets.cmake"
    NAMESPACE NekiraECSLib::
)

# 导出包体为NekiraECSLib
export(PACKAGE NekiraECSLib)