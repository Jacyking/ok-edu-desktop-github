project(UIWindow)

add_definitions(-DOK_${PROJECT_NAME}_MODULE="${PROJECT_NAME}")

include_directories(${CMAKE_SOURCE_DIR}/plugins/include)

set(${PROJECT_NAME}_FORMS 
 widget/LoginWidget.ui
        widget/PluginManagerForm.ui
        widget/BannerWidget.ui
        window/LoginWindow.ui
        window/MainWindow.ui
        window/VideoPlayer.ui 
)

qt5_wrap_ui(${PROJECT_NAME}_FORMS
       
)

set(${PROJECT_NAME}_SOURCES
        widget/playerwidget.cpp
        widget/SettingItem.cpp
        widget/SettingView.cpp
        widget/LoginTitleBar.cpp
        widget/VideoWidget.cpp
        widget/LoginWidget.cpp
        widget/LoginWidget.h
        widget/OResizeWidget.cpp
        widget/OWebView.cpp
        widget/WhiteboardWidget.cpp
        widget/MaterialView.cpp
        widget/OWidget.cpp
        widget/BannerWidget.cpp
        widget/BannerWidget.h

        page/calendar.cpp
        page/email.cpp
        page/Page.cpp
        page/personal.cpp
        page/SettingsPage.cpp
        page/welcome.cpp

        window/LoginWindow.h
        window/LoginWindow.cpp
        window/MainWindow.h
        window/MainWindow.cpp
        window/OWindow.cpp
        window/VideoPlayer.cpp
        window/RoomSelectDialog.cpp

        BaseWindow.cpp
        whiteboard.cpp
        widgetfactory.cpp

        layout/FlowLayout.cpp
        style/MaskLabel.cpp
)


qt5_add_translation(${PROJECT_NAME}_QM_FILES
        translations/de.ts
        translations/es.ts
        translations/fr.ts
        translations/it.ts
        translations/ja.ts
        translations/ko.ts
        translations/pt.ts
        translations/ru.ts
        translations/zh_CN.ts
        translations/zh_TW.ts
        translations/ar.ts
)


if(ENABLE_PLUGINS)
    list(APPEND ${PROJECT_NAME}_FORMS 
        widget/PluginItemForm.ui
        widget/PluginInfoForm.ui
        )

    list(APPEND  ${PROJECT_NAME}_SOURCES               
        widget/PluginManagerForm.h
        widget/PluginManagerForm.cpp
        widget/PluginItemForm.h
        widget/PluginItemForm.cpp
        widget/PluginInfoForm.h
        widget/PluginInfoForm.cpp)
endif()


file(WRITE "${PROJECT_BINARY_DIR}/translations.qrc.in"
"<!DOCTYPE RCC>
<RCC version=\"1.0\">
  <qresource prefix=\"/translations/${PROJECT_NAME}\">
")

foreach (qm ${${PROJECT_NAME}_QM_FILES})
    get_filename_component(qm_name ${qm} NAME)
    file(APPEND "${PROJECT_BINARY_DIR}/translations.qrc.in"
        "    <file alias=\"${qm_name}\">${qm}</file>\n")
endforeach (qm)

file(APPEND "${PROJECT_BINARY_DIR}/translations.qrc.in"
"  </qresource>
</RCC>")

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${PROJECT_BINARY_DIR}/translations.qrc.in
    ${PROJECT_BINARY_DIR}/translations_${PROJECT_NAME}.qrc)

qt5_add_resources(
    ${PROJECT_NAME}_RESOURCES
    ${PROJECT_BINARY_DIR}/translations_${PROJECT_NAME}.qrc
)

add_library(${PROJECT_NAME}
    ${${PROJECT_NAME}_FORMS}
    ${${PROJECT_NAME}_RESOURCES}
    ${${PROJECT_NAME}_QM_FILES}
    ${${PROJECT_NAME}_SOURCES})

if(MSVC)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif (MSVC)
