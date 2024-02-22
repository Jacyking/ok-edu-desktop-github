project(Painter)

add_definitions(-DOK_${PROJECT_NAME}_MODULE="${PROJECT_NAME}")
add_definitions(-DOK_${PROJECT_NAME}_TRANSLATIONS="translations_${PROJECT_NAME}")

include_directories(${GLOOX_DIR}/include)

set(${PROJECT_NAME}_SOURCES
        # ColorPanel.cpp
        PainterMdiArea.cpp
        SharedPaintManager.cpp
        Util.cpp
        DefferedCaller.cpp
        painterrenderer.cpp
        SharedPaintTask.cpp

        WhiteboardController.cpp
        OkGraphicsTextItem.h
        OkGraphicsTextItem.cpp
        PainterWidgetProxy.cpp

        PainterView.h
        PainterView.cpp
        SharedPaintCommand.cpp

        painterdispatcher.cpp
        SharedPaintCommandManager.cpp

        painterevent.cpp
        SharedPainterScene.cpp


        OPainterToolBox.ui
        OPainterToolBox.cpp
        OPainterViewport.ui
        OPainterViewport.h
        OPainterViewport.cpp

        OVideoViewport.h
        OVideoViewport.cpp
        OVideoViewport.ui

        OPainterColorPanel.h
        OPainterColorPanel.cpp
        OPainterColorPanel.ui

        PageClassing.h
        PageClassing.cpp
        PageClassing.ui

        Painter.h
        Painter.cpp
)
qt5_add_resources(
        ${PROJECT_NAME}_RESOURCES
        painter.qrc
)

add_library(
        ${PROJECT_NAME}
        ${${PROJECT_NAME}_SOURCES}
        ${${PROJECT_NAME}_RESOURCES}
)

target_link_libraries(
        ${PROJECT_NAME}
        Smartboard
)


if (MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)