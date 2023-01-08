#          Copyright Rein Halbersma 2019-2023.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.24)
project(
    tabula
    HOMEPAGE_URL https://github.com/rhalbersma/${PROJECT_NAME}
    LANGUAGES CXX
)

add_library(
    ${PROJECT_NAME} INTERFACE
)

set(project_include_dir
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)

target_include_directories(
    ${PROJECT_NAME} INTERFACE
    ${project_include_dir}
)

# {fmt} has -Wshadow and -Wsign-conversion errors that are deliberately ignored in its build config.
# The SYSTEM flag will treat {fmt} on the same footing as system headers and ignore these warnings.
target_include_directories(
    ${PROJECT_NAME} SYSTEM INTERFACE
    SYSTEM ${PROJECT_SOURCE_DIR}/../third_party/fmt/include
)

target_compile_features(
    ${PROJECT_NAME} INTERFACE
    cxx_std_23
)

include(CTest)
add_subdirectory(test)
add_subdirectory(example)
