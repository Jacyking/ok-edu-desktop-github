project(Network)

set(${PROJECT_NAME}_SOURCES
        ImageLoader.cpp
        NetworkHttp.h
        NetworkHttp.cpp
        )

add_subdirectory(backend)

add_library(${PROJECT_NAME}  ${${PROJECT_NAME}_SOURCES})

if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)