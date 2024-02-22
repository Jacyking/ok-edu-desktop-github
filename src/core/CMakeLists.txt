project(OkCore)

include_directories(../..)
include_directories(../../modules)

set(${PROJECT_NAME}_SOURCES
        application.h
        application.cpp
        launcher.cpp
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

if (MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)
