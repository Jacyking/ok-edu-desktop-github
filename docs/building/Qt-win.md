# 准备 Qt 环境
## 下载 Qt 
> 这里为了大家方便建议下载我已经编译好的版本。
> 建议使用版本 **5.15.x**

[下载Qt](https://chuanshaninfo.com/download/Qt)，按需选择版本：
> 链接：https://chuanshaninfo.com/download/Qt
```

# windows平台静态Release版
Qt5.15.7-Windows-x86_64-VS2019-16.11.20-staticFull-20221103.7z
# windows平台静态Debug版
Qt5.15.11-Windows-x86_64-VS2022-staticFull-debug.zip
```


## 解压到对应位置即可
放置位置：E:\Qt，比如我的：E:\Qt\Qt5.15.6-Windows-x86_64-VS2019-16.11.18-staticFull

## 配置环境变量
该步骤就需要配置环境变量指向Qt安装目录，以便于CMake能识别到Qt，请配置环境变量Qt5Static_HOME，方法如下：
```shell
# 桌面打开命令行（或者按快捷键CTRL+r运行），输入命令`SystemPropertiesAdvanced`回车
QTDIR=E:\Qt\Qt5.15.6-Windows-x86_64-VS2019-16.11.18-staticFull
# 是否静态Qt
LINK_STATIC_QT=TRUE
```

# 动态 Qt
按照Qt安装包正常安装选择：
- msvc64 位运行库即可。


