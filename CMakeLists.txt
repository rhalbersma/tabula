cmake_minimum_required(VERSION 3.13)
project(tabula CXX)

set(project_include_dir
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>
)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost 1.69.0 REQUIRED)

add_library(tabula INTERFACE)
target_include_directories(tabula INTERFACE
	${project_include_dir}
)

target_compile_features(tabula INTERFACE cxx_std_17)

add_subdirectory(example)
include(CTest)
add_subdirectory(test)
