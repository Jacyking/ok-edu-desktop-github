# VS Code 开发

## 配置 VS Code 插件
> 配置 C/C++ 开发环境有两种方案，推荐第一种（Clang+LLDB方案）因为MSVC方案的实在很慢！
- 安装通用拓展
  - CMake
  - CMake Tools
- 方案一：Clang+LLDB方案
  - 安装LLVM项目 [下载地址](https://github.com/llvm/llvm-project/releases) 选择最新版，比如：LLVM-16.0.2-win64.exe
  - 安装拓展列表：
    - Clangd
    - Clang-Format
    - CodeLLDB
    - APT系，执行命令 `sudo apt install -y clangd`
    - Yum系，自行解决
    - macOS，自行解决
- 方案二：MSVC方案
  - 安装VS2022
  - 安装拓展列表：
    - C/C++
    - C/C++ Extension Pack
    - C/C++ Themes(可选)

> 手动安装拓展（因为大陆网络原因组件无法自动下载）
  - 下载请移步 [vscode](https://pan.baidu.com/s/1Q6HGMkbGKzNxaspnSib8BA) 提取码: `wqp2` 下载对应拓展包
  - 点击：左侧栏->拓展->[...]->从VSIX安装，选择拓展包安装即可。

## 编译项目
  - 打开项目，进入源代码根目录，右键以 `VS Code `打开项目即可。
  - 顶部弹出菜单，选择 [VS 2022 Release - amd64] 或者 [Clang - amd64] 配置项
  - 底部菜单，选择 [Release] 构建
## CMake编译
- 点击左侧CMake菜单，打开CMake框，可以查看显示所有的模块项目； 
- 点击上边右侧第一个 `Configure All Project` 配置项目，输出正常结束即可； 
- 点击上边右侧第二个 `Build All Project` 编译项目，等待几分钟即可输出程序可执行文件；
