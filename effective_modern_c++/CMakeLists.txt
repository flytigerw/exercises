


file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")


foreach(src ${srcs})
    get_filename_component(name src NAME_WE)
    add_executable(name ${src})
endforeach()
