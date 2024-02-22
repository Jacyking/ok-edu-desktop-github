project(Settings)

set(${PROJECT_NAME}_RESOURCES
        translator.h
        translator.cpp
        OkSettings.h
        OkSettings.cpp
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_RESOURCES})

if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)