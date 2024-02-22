# Windows 平台编译
> 目前在Windows 10测试通过，最好在Win10以上系统编译开发。

## 安装依赖
下载如下依赖库
- Python  (3.8.x)  https://www.python.org/downloads/
- Perl    (5.12.x) https://strawberryperl.com/releases.html
- CMake   (3.25.x)    https://cmake.org/download/
- MinGW64 (latest)    https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/

## 配置环境变量
上一步，安装完依赖程序之后，打开命令行（或者按快捷键CTRL+r运行），输入命令`SystemPropertiesAdvanced`回车，
设置系统环境变量（用户级和系统级均可），如下
```cmd
# 在原有PATH之上，增加如下（具体路径根据自己的安装路径修改）
PATH=C:\strawberry-perl\perl\bin;C:\Program Files\CMake\bin;C:\MinGW\bin;
```

## 安装 Visual studio 环境
- 配置 桌面开发
- 配置 CMake工具支持
- 配置 Clang支持
- 配置 Windows 11 SDK(10.0.22000.0)
> 注意：MSVC版本最好使用14.37.xxxx(其它版本可能编译报错)，CMake 配置时信息如下：
```shell
[CMake] -- CMAKE_CXX_COMPILER=E:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.37.{xxxx}/bin/Hostx64/x64/cl.exe
```