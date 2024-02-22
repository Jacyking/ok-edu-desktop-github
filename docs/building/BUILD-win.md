# Windows 平台编译

## 所需依赖

```cmd
# Python  (3+)  https://www.python.org/downloads/
# Perl    (5.12+) https://strawberryperl.com/releases.html
# CMake   (3+)    https://cmake.org/download/
# Conan   (latest)  https://conan.io/

# 配置环境变量
PATH =${python_dir}\bin;${perl_dir}\bin;${cmake}\bin;
```

> 安装 Conan（python 组件）

```sh
pip install conan
```

> Visual Studio 2022 + 配置桌面开发 + Clang

> Windows SDK 10


## 构建方法

构建客户需要使用【**静态**】构建模式，由于一些原因不能动态。

> 方法一【**推荐**】

    下载静态构建的Qt和WebRTC静态库

> 方法二【**不推荐**】

    自编译静态Qt+自编译静态WebRTC库，此方法需要梯子以及编译环境影响编译难度高。

## 构建 Qt（方法一）

> 下载静态版 Qt

    位置：https://build-qt.fsu0413.me/，找到5.15最新**静态64位**版本
    比如我的：Qt5.15.6-Windows-x86-VS2019-16.11.18-staticFull-20220915.7z

> 安装对应位置即可

    E:\Qt\Qt5.15.6-Windows-x86-VS2019-16.11.18-staticFull

> 配置环境变量

    QTDIR=E:\Qt\Qt5.15.6-Windows-x86-VS2019-16.11.18-staticFull

## 构建 Qt（方法二）

> 下载 Qt 源码

```sh
https://mirrors.tuna.tsinghua.edu.cn/qt/official_releases/qt/5.15/5.15.6/single/qt-everywhere-opensource-src-5.15.6.zip
```

> 参考

    https://wiki.qt.io/Building_Qt_5_from_Git#Windows

> 解压源码

    qt-everywhere-opensource-src-5.15.6

> 配置(msvc)

```sh
# 用管理员模式打开VS2017本机命令行提示符，执行如下
configure -static -release -opensource -confirm-license -platform win32-msvc -nomake tests -nomake examples -mp -prefix E:/Qt/Qt-5.15.6-static
```

> 编译安装

    nmake && nmake install

> 清理（如需）

    nmake /f makefile clean

> 配置环境变量

    QTDIR=E:/Qt/Qt-5.15.6-static


## 构建第三方包

为了提升项目构建效率，采用了 [Conan](https://conan.io/) 包管理工具，过程如下：

> 执行安装

```shell
# 静态选项：compiler.runtime=MT 取消强依赖：--build=missing
conan install . -s compiler.runtime=MT --build=missing 
# 如果遇到网络问题则需要多次执行，或者配置代理 ${user_home}/.conan/conan.conf。
```

## 准备 WebRTC 库环境
### 方法一（推荐）

> 从百度网盘下载对应包

```
链接: https://pan.baidu.com/s/1Q6HGMkbGKzNxaspnSib8BA 提取码: wqp2
```

> 放置目录

```
3rdparty/webrtc/
├── libwebrtc-windows-x64
│   ├── debug
│   ├── include
│   ├── release
```

### 方法二

> 配置 Proxy（如需）

```sh
# 设置 proxy
set HTTP_PROXY=http://{ip}:{port}
set HTTPS_PROXY=http://{ip}:{port}
git config --global http.proxy socks5://{ip}:{port}
git config --global https.proxy socks5://{ip}:{port}
# 取消 proxy
set HTTP_PROXY
set HTTPS_PROXY
git config --global --unset http.proxy
git config --global --unset https.proxy
```

> 下载 depot_tools

```sh
#下载depot_tools
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git

# 设置环境变量：
set PATh=${depot_tools_dir};%PATH%

#　参考：
https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html
```

> 下载 WebRTC 源码

```bash
# 准备目录
rd /s /q webrtc & mkdir webrtc
# 配置源码repo地址
gclient config --name src https://webrtc.googlesource.com/src
# 这个过程需要多次进行，且易断开
gclient sync
```

> 执行编译

```sh
# gn
/webrtc/src$ gn gen  ../out/Release_{YYMMDD} --args='is_debug = false rtc_include_tests = false use_lld = false enable_iterator_debugging = true use_custom_libcxx = false use_custom_libcxx_for_host = false'
# ninja
/webrtc/src$ ../../depot_tools/ninja -C ../out/Release_{YYMMDD} webrtc
```


```ini
[proxies]
# http = http://user:pass@10.10.1.10:3128/
# http = http://10.10.1.10:3128
# https = http://10.10.1.10:1080
```
## 构建 Gloox

> 更新代码

```sh
# 在项目平级克隆gloox库
git clone https://gitee.com/chuanshantech/ok-edu-gloox.git
```

> 用 visual studio 打开 gloox 解决方案，如下配置：
- 目标：Release、x64
- 配置类型：静态库(.lib)
- 目标文件拓展名：.lib
- 运行库：MT
- 增加宏定义：HAVE_OPENSSL
- 配置boringssl头文件: ${libwebrtc_dir}\include\third_party\boringssl\src\include
- 属性-C/C++-优化-全程序优化: 否

> 生成目标

```
# 目标位置
gloox\{Release,Debug}
```
