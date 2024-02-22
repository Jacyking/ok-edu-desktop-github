# 项目编译与构建
## 安装依赖
> Ubuntu 20+
```shell
sudo apt-get install build-dep 
sudo apt-get install build-essential perl python3 git
sudo apt-get install libudev-dev libmtdev-dev libinput-dev libdrm-dev libgbm-dev libgtk-3-devlibkrb5-dev
sudo apt-get install libssl-dev libcrypt-dev

# Qt xcb
sudo apt-get install libxcb* libxkb* libfontconfig1-dev libfreetype6-dev libx11-dev libx11-xcb-dev libxext-dev libxfixes-dev libxi-dev libxrender-dev

# Qt Multimedia
sudo apt-get install libasound2-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-good1.0-dev libgstreamer-plugins-bad1.0-dev

# sqlite sqlcipher
apt install libsqlite3-dev libsqlcipher-dev

# vpx qrencode sodium
apt install libvpx-dev libjpeg-dev libtiff-dev libpng16-16 libpng-dev libavcodec-dev libavdevice-dev libqrencode-dev libsodium-dev 
```

## 下载 Qt 源码

```shell
wget https://mirrors.tuna.tsinghua.edu.cn/qt/official_releases/qt/5.15/5.15.6/single/qt-everywhere-opensource-src-5.15.6.zip
```

### 编译 Qt 源码（Linux）

- 参考 https://doc.qt.io/qt-5/linux-requirements.html

> 配置

```shell
./configure -static -release -xcb -fontconfig -system-freetype -opensource -confirm-license -nomake examples -skip qtwebengine -prefix /opt/Qt-5.15.6-static
```

> 编译、安装

```shell
make && sudo make install
```

> 设置环境变量

```shell
gaojie@root-host:~$ cat /etc/profile.d/develop.sh 
#Qt 静态目录
export QTDIR=/opt/Qt-5.15.6-static
```

## 下载源代码

```shell
#客户端
git clone  https://gitee.com/chuanshantech/ok-edu-classroom-desktop.git
#gloox库
git clone  https://gitee.com/chuanshantech/ok-edu-gloox.git gloox
```

### 构建 WebRTC（方法一）

> 准备目录

```shell
  mkdir {root}/webrtc-build
```

> 配置代理

```shell
# 由于需要通过谷歌下载代码所以需要准备梯子
set HTTP_PROXY=http://{ip}:{port}
set HTTPS_PROXY=http://{ip}:{port}
git config --global http.proxy socks5://{ip}:{port}
git config --global https.proxy socks5://{ip}:{port}
# 取消梯子
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

> 构建 WebRTC（方法二）

```shell
# 从百度网盘下载对应包
链接: https://pan.baidu.com/s/1Q6HGMkbGKzNxaspnSib8BA 提取码: wqp2
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

> 下载代码
```shell
git clone https://gitee.com/chuanshantech/ok-edu-gloox.git gloox
```

> 编译代码

```shell
$ cd 3rdparty/gloox

# Debug
$ CC=clang CXX=clang++ ./configure --prefix=`pwd`/Debug --enable-debug=yes --with-gnutls=no --with-openssl=yes --with-tests=no && make -j`(nproc)` && make install

# Release
$ CC=clang CXX=clang++ ./configure --prefix=`pwd`/Release --enable-debug=no --with-gnutls=no --with-openssl=yes --with-tests=no && make -j`(nproc)` && make install

# 检查编译输出静态库
$ ls {Debug,Release}/lib/libgloox.a
```

# 构建和运行

- 使用[**CMake**]构建；

```shell
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

- 使用[VS Code](IDE-vscode.md)构建；
- 使用[VS Studio](IDE-vsstudio.md)构建；
