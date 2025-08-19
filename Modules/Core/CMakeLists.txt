# ==============================================
# Core Module
# ==============================================

# headers
file(GLOB_RECURSE CORE_HEADERS
    "Public/*.hpp"
)

# sources
file(GLOB_RECURSE CORE_SOURCES
    "Private/*.cpp"
)

# 创建库
add_library(Core SHARED ${CORE_HEADERS} ${CORE_SOURCES})

# include路径
target_include_directories(Core
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Public>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/Core>

    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Public
)


# ==============================================
# 安装设置
# ==============================================

include(GNUInstallDirs)

# 安装头文件
install(DIRECTORY Public/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Core
    FILES_MATCHING PATTERN "*.hpp"
)
