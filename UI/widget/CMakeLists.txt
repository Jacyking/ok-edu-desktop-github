project(UIWidget)


set(${PROJECT_NAME}_RESOUCRES MoveableBar.cpp)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_RESOUCRES})

if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)