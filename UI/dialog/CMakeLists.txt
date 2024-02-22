# 这里指定当前模块名，这里推荐用文件名作为模块名
set(UIDialog_SOURCES
#    progressdialog.cpp
#    VideoPlayerDialog.cpp
    DialogUtils.cpp
)

add_library(UIDialog  ${UIDialog_SOURCES})