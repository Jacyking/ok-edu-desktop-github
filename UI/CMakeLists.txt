project(UI)

set(${PROJECT_NAME}_SOURCES
        WindowManager.h
        WindowManager.cpp
        resources.cpp

        dialog/VideoPlayerDialog.cpp
        dialog/DialogUtils.cpp
        dialog/progressdialog.cpp

        #        ./multimedia/Camera.cpp

        dialog/VideoPlayerDialog.ui

        component/OMainMenu.ui
        component/OMainMenu.h
        component/OMainMenu.cpp
        component/OMainTitleBar.ui
        component/OMainTitleBar.h
        component/OMainTitleBar.cpp
        component/OTitleClose.ui
        component/OTitleClose.cpp

        component/OPlayerController.ui
        component/OPlayerController.cpp

        component/OVideoPlayer.ui
        component/OVideoPlayer.cpp

        component/OVideoWidget.ui
        component/OVideoWidget.cpp
        component/OTitleBar.ui
        component/OTitleBar.cpp
        component/OCountDown.ui
        component/OCountDown.cpp
        component/OPlayerWidget.ui
        component/OPlayerWidget.cpp

)

add_subdirectory(core)
add_subdirectory(window)
add_subdirectory(widget)


add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

if (MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)