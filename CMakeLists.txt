cmake_minimum_required(VERSION 3.15)
project(
    tabula
    HOMEPAGE_URL https://github.com/rhalbersma/${PROJECT_NAME}
    LANGUAGES CXX
)

add_library(
    ${PROJECT_NAME} INTERFACE
)

find_package(Boost REQUIRED)
target_link_libraries(
    ${PROJECT_NAME} INTERFACE
    Boost::boost
)

set(project_include_dir
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)
target_include_directories(
    ${PROJECT_NAME} INTERFACE
    ${project_include_dir}
)

target_compile_features(
    ${PROJECT_NAME} INTERFACE
    cxx_std_17
)

include(CTest)
add_subdirectory(test)
add_subdirectory(example)
