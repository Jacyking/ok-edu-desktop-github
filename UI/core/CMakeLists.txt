project(UICore)
set(UICore_SOURCES
    ControllerManager.cpp
    FontManager.cpp
    I18N.cpp
    SettingManager.cpp
    ui.h
)

add_library(UICore  ${UICore_SOURCES})

if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)