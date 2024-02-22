include_directories(${CMAKE_SOURCE_DIR}/3rdparty)

add_subdirectory(im)

if(ENABLE_MODULE_PAINTER)
add_subdirectory(painter)
endif ()

