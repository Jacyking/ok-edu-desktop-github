# 构建第三方包

由于本项目依赖众多[第三方库](../../README.md#-第三方库)，
为了提升项目构建效率，采用了 [Conan](https://conan.io/) 包管理工具，操作过程如下：

## 安装 Conan
> Conan 最新2.x版本目前很多包不支持请下载v1.59.0版本，操作如下

```sh
# 卸载最新版(如果已安装)
pip uninstall conan
# 安装 1.x 版本
pip install conan==1.59.0
```

## 安装依赖
安装命令如下
> 这个过程需要需要花费很长时间，由于网络原因可能中断，需要多次执行安装命令等到输出成功消息。
```shell
# 静态选项：compiler.runtime=MT(MTd调试) 取消强依赖：--build=missing
conan install . -s compiler.runtime=MT --build=missing
```

## 3rdparty第三方包 
> 也可以直接下载我们已经编译好的，已经包含webrtc、gloox依赖包。
> 下载地址：https://chuanshaninfo.com/download/3rdparty-windows-x64.zip

### 准备 WebRTC 库
提供了两种方法选其一即可，参考如下:
- 方法一：下载现成编译好的webrtc库；
- 方法二：下载webrtc源码自行编译（大陆的网络由于某些原因几乎无法下载
**极不**建议该种方法，外面的同学可以试试！）。

#### 方法一（推荐）


- 放置目录，结构如下：
```
# 如果不存在的目录，请创建。
3rdparty/webrtc/
├── libwebrtc-windows-x64
│   ├── include
│   ├── release
```

#### 方法二（不推荐）

- 科学配置Proxy修改自己的IP（位于大陆的同学）

```sh
# 设置proxy
set HTTP_PROXY=http://{ip}:{port}
set HTTPS_PROXY=http://{ip}:{port}
git config --global http.proxy socks5://{ip}:{port}
git config --global https.proxy socks5://{ip}:{port}
# 取消proxy
set HTTP_PROXY
set HTTPS_PROXY
git config --global --unset http.proxy
git config --global --unset https.proxy
```

- 下载 depot_tools

```sh
#下载depot_tools
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
# 设置环境变量：
set PATh=${depot_tools_dir};%PATH%
#　参考：
https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html
```

- 下载 WebRTC 源码

```bash
# 准备目录
rd /s /q webrtc & mkdir webrtc
# 配置源码repo地址
gclient config --name src https://webrtc.googlesource.com/src
# 这个过程需要多次进行，且易断开
gclient sync
```

- 执行编译
    
打开Powershell，执行如下命令：
```sh
# gn 配置
/webrtc/src$ gn gen  ../out/Release --args='is_debug = false rtc_include_tests = false use_lld = false enable_iterator_debugging = true use_custom_libcxx = false use_custom_libcxx_for_host = false'
# ninja 编译
/webrtc/src$ ../../depot_tools/ninja -C ../out/Release webrtc
# 创建头文件输出目录(/out/include)
New-Item ../out/include -ItemType Directory -Force
# 复制头文件，${WEBRTC_DIR}为webrtc代码目录
robocopy "$WEBRTC_DIR\src" "..\out\include" *.h *.hpp /S /NP /NS /NC /NFL /NDL
```

- 放置目录，结构如下：

```
# 如果不存在的目录，请创建。
3rdparty/webrtc/
├── libwebrtc-windows-x64
│   ├── include
│   ├── release
```

### 准备 Gloox 库
- 配置项目
由于项目是基于[XMPP](https://xmpp.org)协议，[Gloox](https://camaya.net/gloox/)是该协议的实现库，本项目需要对其做了拓展
代码位于 https://gitee.com/okstar-org/ok-gloox.git。 


- 构建生成项目，用 visual studio 打开 gloox 目录或者以CMake方式打开CMakeLists.txt
    1. 配置项目：【项目】-》【xx的配置】
    2. 增加配置：【x64-Debug】和【x64-Release】，选择对应构建类型，工具集选择【msvc_x64_64】

> CMake参考 https://learn.microsoft.com/zh-cn/cpp/build/cmake-projects-in-visual-studio?view=msvc-170

- 输出头文件
```
# 执行拷贝头文件命令
E:\QtWorkspace\ok-gloox>robocopy "src" "x64\include" *.h *.hpp /S /NP /NS /NC /NFL /NDL
# 查看输出目录（由于VS的配置可能不一样）
E:\QtWorkspace\ok-gloox>dir x64
 Directory of E:\QtWorkspace\ok-gloox\x64
2023/05/04  21:42    <DIR>          .
2023/05/04  21:42    <DIR>          ..
2023/04/27  21:21    <DIR>          include
2023/04/22  16:57    <DIR>          Release
```

- 配置 Gloox 依赖
拷贝gloox生成的依赖放到主项目，位置如下：
```
E:\QtWorkspace\ok-edu-classroom-desktop\3rdparty\gloox  #没有请创建
└── libgloox-windows-x64  #没有请创建
    ├── include/gloox/*.h #复制所有头文件（x64/include/*.h）到此处
    └── release/gloox.lib #复制gloox.lib库文件（x64/Release/gloox.lib去掉版本）到此处
```

## 最终3rdparty结构
```
OkEDU-Classroom-Desktop$ tree  -L 4 3rdparty/
3rdparty/
├── gloox
│   └── libgloox-linux-x86_64
│       ├── debug
│       │ ├── libgloox.a
│       └── include
│           └── gloox   //gloox 头文件目录
└── webrtc
    └── libwebrtc-linux-x86_64
        ├── debug
        │   └── libwebrtc.a
        └── include             //webrtc 头文件目录
            ├── api
            ├── audio
             --ignore--
            ├── tools
            └── video

```