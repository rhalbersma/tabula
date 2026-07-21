#          Copyright Rein Halbersma 2019-2026.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

set(cxx_compile_options_debugsym
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
        -g
    >
)

set(current_source_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE targets RELATIVE ${current_source_dir} *.cpp)

foreach(t ${targets})
    get_filename_component(target_path ${t} PATH)
    get_filename_component(target_name_we ${t} NAME_WE)
    string(REPLACE "/" "." target_id ${target_path}/${target_name_we})
    string(REGEX REPLACE "^[.]" "" target_id ${target_id})

    add_executable(${target_id} src/${t})

    target_link_libraries(
        ${target_id} PRIVATE
        ${CMAKE_PROJECT_NAME}
        tabula_test_options
        # winlibs MinGW splits <print>'s terminal-write internals
        # (std::__open_terminal, std::__write_to_terminal) into a separate
        # static lib that isn't pulled in automatically.
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<PLATFORM_ID:Windows>>:stdc++exp>
    )

    target_compile_options(
        ${target_id} PRIVATE
        ${cxx_compile_options_debugsym}
    )
endforeach()
