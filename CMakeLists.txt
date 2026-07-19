#          Copyright Rein Halbersma 2019-2025.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.28)
project(
    tabula
    VERSION 0.1.0
    DESCRIPTION "Board game utilities"
    HOMEPAGE_URL "https://github.com/rhalbersma/tabula"
    LANGUAGES CXX
)

include(GNUInstallDirs)

add_library(
    ${PROJECT_NAME} INTERFACE
)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# No target_include_directories: the HEADERS file set below adds its base
# directory to the build interface, and install(TARGETS ... FILE_SET) adds
# the install destination to the install interface.
target_compile_features(
    ${PROJECT_NAME} INTERFACE
    cxx_std_23
)

target_sources(
    ${PROJECT_NAME} INTERFACE
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        include/tabula/board.hpp
        include/tabula/compass.hpp
        include/tabula/concepts.hpp
        include/tabula/dihedral.hpp
        include/tabula/embedding.hpp
        include/tabula/format.hpp
        include/tabula/functional.hpp
        include/tabula/games.hpp
        include/tabula/games/chess.hpp
        include/tabula/games/draughts.hpp
        include/tabula/games/stratego.hpp
        include/tabula/grids.hpp
        include/tabula/grids/chequer.hpp
        include/tabula/grids/rectangle.hpp
        include/tabula/lake.hpp
        include/tabula/padding.hpp
        include/tabula/square.hpp
        include/tabula/tuple.hpp
        include/tabula/vector.hpp
)

# Tests and examples (and their Boost.Test dependency) only exist when
# tabula itself is being developed. Consumers vendoring this directory via
# add_subdirectory or FetchContent get just the header-only target, with no
# BUILD_TESTING workaround required on their side.
if(PROJECT_IS_TOP_LEVEL)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(test)
        add_subdirectory(example)
    endif()
endif()

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    FILE_SET HEADERS
)
install(
    EXPORT ${PROJECT_NAME}Targets
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Package config + version files, so consumers can locate the installed
# package with find_package(tabula CONFIG). ARCH_INDEPENDENT because a
# header-only library has no architecture-specific binaries.
include(CMakePackageConfigHelpers)
configure_package_config_file(
    cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    COMPATIBILITY SameMinorVersion
    ARCH_INDEPENDENT
)
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
