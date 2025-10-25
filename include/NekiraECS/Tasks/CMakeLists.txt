# ======================================
# Tasks/CMakeLists.txt
# ======================================
include(GNUInstallDirs)

# headers
file(GLOB_RECURSE CORE_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")
# sources
file(GLOB_RECURSE CORE_SOURCES "${CMAKE_SOURCE_DIR}/source/Tasks/*.cpp")

# 创建NekiraECSTasks模块
add_library(NekiraECSTasks SHARED ${CORE_HEADERS} ${CORE_SOURCES})
add_library(NekiraECSLib::NekiraECSTasks ALIAS NekiraECSTasks)

# include目录
target_include_directories(NekiraECSTasks 
    PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

    PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# install
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/NekiraECS/Tasks
    FILES_MATCHING PATTERN "*.hpp"
)