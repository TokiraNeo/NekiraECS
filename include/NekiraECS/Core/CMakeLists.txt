# ========================================
# Core/CMakeLists.txt
# ========================================
include(GNUInstallDirs)

# headers
file(GLOB_RECURSE CORE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
# sources
file(GLOB_RECURSE CORE_SOURCES "${CMAKE_SOURCE_DIR}/source/Core/*.cpp")

# 创建NekiraECSCore模块的目标
add_library(NekiraECSCore SHARED ${CORE_HEADERS} ${CORE_SOURCES})
add_library(NekiraECSLib::NekiraECSCore ALIAS NekiraECSCore)

# include目录
target_include_directories(NekiraECSCore 
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# install
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/NekiraECS/Core
    FILES_MATCHING PATTERN "*.hpp"
)