


file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")


find_package(GTest REQUIRED)

foreach(src ${srcs})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
    target_link_libraries(${name} gtest pthread)
endforeach()
