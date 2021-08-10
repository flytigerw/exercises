

cmake_minimum_required(VERSION 3.15)

project(exercises)


set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

macro(populate_source_vars dir res)
    file(GLOB ${res} "${ROOT_DIR}/${dir}/*.cc")
endmacro()

macro(build_exec name srcs)
    add_executable(${name} ${srcs})
endmacro()


set(permutation_srcs)
populate_source_vars(permutation permutation_srcs)

build_exec(permutation_exec ${permutation_srcs})


add_subdirectory(effective_modern_c++)


