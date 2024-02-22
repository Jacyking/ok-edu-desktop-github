project(Plugin)

include_directories(../../base)
include_directories(iconset/)
include_directories(${CMAKE_SOURCE_DIR}/plugins/include)


set(${PROJECT_NAME}_SOURCES
        iconset/anim.h
        iconset/anim.cpp
        iconset/iconset.h
        iconset/iconset.cpp
        varianttree.h
        varianttree.cpp
        optionstree.h
        optionstree.cpp
        OkOptions.h
        OkOptions.cpp
        pluginhost.h
        pluginhost.cpp
        pluginmanager.h
        pluginmanager.cpp
        PluginInfo.h
        PluginInfo.cpp
        textutil.h
        textutil.cpp
        coloropt.h
        coloropt.cpp
        common.h
        common.cpp
)

add_library(${PROJECT_NAME}  ${${PROJECT_NAME}_SOURCES})


if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)