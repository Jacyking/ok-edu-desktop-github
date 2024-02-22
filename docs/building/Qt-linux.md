# 准备 Qt 环境

> 这里为了大家方便建议下载我已经编译好的版本。

> 建议使用版本 **5.15.x**

## 方法 1（下载已编译版本）
> 支持Ubuntu 20.04、22.04

[Qt下载地址](https://www.chuanshaninfo.com/download/Qt/)
> 选择对应版本 
- 动态： Qt-5.15.6-linux-shared.zip
- 静态： Qt-5.15.6-linux-static.zip

## 方法 2（源码编译）

- 参考 https://doc.qt.io/qt-5/linux-requirements.html
- 从清华源 [下载源代码](https://mirrors.tuna.tsinghua.edu.cn/qt/official_releases/qt/5.15/5.15.6/single/qt-everywhere-opensource-src-5.15.6.tar.xz)
（请选择tar包，zip在Linux下解压存在换行符问题）
- 配置
```shell
#解压
tar xvf qt-everywhere-opensource-src-5.15.6.tar.xz
#配置
# cd 到源码目录
./configure -opensource -confirm-license -prefix /opt/Qt-5.15.6 \
  -debug-and-release -xcb -fontconfig -system-freetype  \
  -skip qtwebengine -nomake examples #默认动态，增加-static选项，则为静态Qt
```

- 编译、安装
```shell
make && sudo make install
```

## 设置环境变量

```shell
$ vim /etc/profile.d/qt.sh 
#添加配置 Qt 目录，如下：
export QTDIR=/opt/Qt-5.15.6
export LINK_STATIC_QT=FALSE
```