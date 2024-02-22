# 设置Qt配置参数，默认从环境变量读取
set(QT_DIR $ENV{QTDIR})
if(NOT DEFINED QT_DIR)
message(FATAL_ERROR "请在环境变量配置Qt路径【QTDIR】！")
endif()
message(STATUS "QT_DIR=${QT_DIR}")

# 根据Qt类型，设置动态(安装默认)或者静态(下载的静态版)，默认从环境变量读取
set(LINK_STATIC_QT $ENV{LINK_STATIC_QT})
if(NOT DEFINED LINK_STATIC_QT)
message(FATAL_ERROR "请在环境变量配置Qt类型【LINK_STATIC_QT】！")
endif()
message(STATUS "LINK_STATIC_QT=${LINK_STATIC_QT}")

# 开启插件（ON/OFF）
set(ENABLE_PLUGINS ON)

# 开启画板（ON/OFF）
set(ENABLE_MODULE_PAINTER OFF)