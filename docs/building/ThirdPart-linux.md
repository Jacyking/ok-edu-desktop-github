# 安装相关依赖

## 安装系统依赖
> Ubuntu 20+
```shell
sudo apt-get update -y

sudo apt-get install -y libpcre2-dev libudev-dev libmtdev-dev  libinput-dev libdrm-dev libgbm-dev    \
              libgtk-3-dev libkrb5-dev

# ssl libsodium sqlite sqlcipher
sudo apt-get install -y libssl-dev libcrypt-dev libsodium-dev libsqlite3-dev libsqlcipher-dev

# xcb
sudo apt-get install -y libxcb* libxkb* libfontconfig1-dev \
               libfreetype6-dev libx11-dev libx11-xcb-dev \
               libxext-dev libxfixes-dev libxi-dev libxrender-dev libxss-dev 

# Multimedia
sudo apt-get install -y libasound2-dev libgstreamer1.0-dev \
      libgstreamer-plugins-base1.0-dev libgstreamer-plugins-good1.0-dev \
      libgstreamer-plugins-bad1.0-dev libpulse-dev libpulse-mainloop-glib0 libopenal-dev

# sqlite sqlcipher
sudo apt install -y libsqlite3-dev libsqlcipher-dev

# ffmpeg vpx qrencode sodium
sudo apt install -y libvpx-dev libjpeg-dev libexif-dev libtiff-dev libpng16-16 libpng-dev libavcodec-dev libavdevice-dev libqrencode-dev libsodium-dev libopenal-dev 
```
## 3rdparty第三方包
> 也可以直接下载我们已经编译好的，已经包含webrtc、gloox依赖包。
> 下载地址：https://chuanshaninfo.com/download/3rdparty-linux-x64.zip

## 准备 WebRTC 库环境
### 方法一（推荐）

```shell
# 从百度网盘下载对应包
链接: https://pan.baidu.com/s/1Q6HGMkbGKzNxaspnSib8BA 提取码: wqp2
```

### 构建 WebRTC（方法二）

> 准备目录

```shell
  mkdir {root}/webrtc-build
```

> 配置Proxy（大陆）

```shell
# 配置
set HTTP_PROXY=http://{ip}:{port}
set HTTPS_PROXY=http://{ip}:{port}
git config --global http.proxy socks5://{ip}:{port}
git config --global https.proxy socks5://{ip}:{port}
# 取消
set HTTP_PROXY
set HTTPS_PROXY
git config --global --unset http.proxy
git config --global --unset https.proxy
```

> 安装 depot_tools

```shell
# 下载工具
git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
# 配置环境变量
export PATH={root}/webrtc-build/depot_tools:$PATH

# 配置帐号（如果没有配置）
$ git config --global user.name "John Doe"
$ git config --global user.email "jdoe@email.com"
$ git config --global core.autocrlf false
$ git config --global core.filemode false
$ # and for fun!
$ git config --global color.ui true

```

> 参考
- https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up

> 下载 WebRTC 源码
```shell
# 创建webrtc目录
mkdir {root}/webrtc-build/webrtc -p
# 进入webrtc目录
cd {root}/webrtc-build/webrtc
# 配置repo
gclient config --name src https://webrtc.googlesource.com/src
# 同步
gclient sync
```

> 编译 WebRTC 源码

- GN 预处理

```shell
# 输出路径：../out/Debug
/webrtc/src$ ../../depot_tools/gn gen ../out/Debug --args="is_debug = true
  rtc_include_tests = false \
# rtc_build_ssl=false \
# rtc_ssl_root = "/opt/openssl/include" \ #下载openssl(3.0.2版本)编译到/opt/openssl
  use_lld = false \
  use_rtti = true \
  enable_iterator_debugging = true  \
  use_custom_libcxx = false \
  use_custom_libcxx_for_host = false"
```

- 修改 src/rtc_base/BUILD.gn 配置 openssl

```shell
# libs = ["/opt/openssl/lib64/libssl.a", "/opt/openssl/lib64/libcrypto.a"]
rtc_library("rtc_base") {
  visibility = [ "*" ]
  cflags = []
  cflags_cc = [
      "-Wno-error=deprecated-declarations" , "-Wno-deprecated-declarations"
  ]
  libs = ["/opt/openssl/lib64/libssl.a", "/opt/openssl/lib64/libcrypto.a"]
  defines = []
```

- NINJA 编译

```shell
/webrtc/src$ ../../depot_tools/ninja -C ../out/Debug/ webrtc
```


- 放置位置

```shell
# 放置目录
3rdparty/webrtc/
├── libwebrtc-linux-x86_64
│   ├── debug
│   ├── include
│   └── release
├── libwebrtc-windows-x86
│   ├── debug
│   ├── include
│   ├── release
├── libwebrtc-windows-x64
│   ├── debug
│   ├── include
│   ├── release
```

## 构建 Gloox
> 下载gloox库
```shell
git clone  https://gitee.com/chuanshantech/ok-edu-gloox.git gloox
```
> 编译代码

```shell
# 到 gloox 根目录
# 构建 Debug
$ CC=clang CXX=clang++ ./configure --prefix=`pwd`/Debug --enable-debug=yes --with-gnutls=no --with-openssl=yes --with-tests=no && make -j`(nproc)` && make install
# 构建 Release
$ CC=clang CXX=clang++ ./configure --prefix=`pwd`/Release --enable-debug=no --with-gnutls=no --with-openssl=yes --with-tests=no && make -j`(nproc)` && make install
# 检查编译输出静态库
$ ls {Debug,Release}/
```
> 放置位置
```shell
# 将gloox输出目标放置如下位置
3rdparty/gloox/
└── libgloox-linux-x86_64
    ├── debug
    │   ├── libgloox.a
    │   ├── libgloox.la
    │   ├── libgloox.so -> libgloox.so.18.0.0
    │   ├── libgloox.so.18 -> libgloox.so.18.0.0
    │   ├── libgloox.so.18.0.0
    │   └── pkgconfig
    └── include
        └── gloox
```