project(Smartboard)

include_directories(${GLOOX_DIR}/include)

set(${PROJECT_NAME}_SOURCES
        imsmartboard.h
        imsmartboard.cpp
        smartboard.h
        smartboard.cpp
        smartboarddraw.h
        smartboarddraw.cpp
        smartboarddrawtext.h
        smartboarddrawtext.cpp
        smartboardcontrollervoice.h
        smartboardcontrollervoice.cpp
        smartboarddrawremove.h
        smartboarddrawremove.cpp
        smartboardcontrollerselect.h
        smartboardcontrollerselect.cpp
        smartboarddrawmove.h
        smartboarddrawmove.cpp
        smartboardcontroller.h
        smartboardcontroller.cpp
        smartboarddrawline.h
        smartboarddrawline.cpp
        smartboarddrawfile.h
        smartboarddrawfile.cpp
)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SOURCES})

if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)