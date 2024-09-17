![Linux Logo](./logo.jpg)

![Linux Logo](./LinuxOS.jpg)

### Features

```
. Linux_OS
|—— CppCodeSnippets
|   |—— C++ 常用代码片段
|—— CMakeCodeSnippets
|   |—— CMake 常用代码片段
|—— PythonCodeSnippets
|   |—— Python 常用代码片段
|—— vscode
|   |—— VSCode 常用技巧以及配置
|   |—— VS 项目属性配置说明
|—— UbuntuConfig
|   |—— README Ubuntu常用配置说明
|—— DebianConfig
|   |—— README Debian常用配置说明
|—— VSLinux
|   |—— Visual Studio 配置 Linux 开发环境
|—— Logo.png
|—— README.md
```

--------------------------------------------------------------------------------
### Powershell on Windows Terminal

```powershell
# git bash
# 将 'D:\Git\usr\bin' 添加到环境变量, 可以使用 Linux 一些常用命令

# 在终端打开当前路径(文件资源管理器) on Windows
start .

# 在终端打开文件资源管理器 on Mac
open .
```

### Linux Operating System

- Configureation
- LinuxFundation
- SystemProgrammingCPlusPlus


### Linux Command line Tricks

```shell
# 快速回到上一次的目录
cd -

# 快速回到 home/user 目录
cd ~

# 终端清屏
clear
# 使用快捷键 Ctrl + l

# 快速重启 shell
reset

# 关闭终端 shell
# 使用快捷键 Ctrl + d

# pushd 将一个特定的目录压入栈中保存 and popd 将栈中目录弹出, 回到特定目录
pushd /etc/gcc
# 经过一系列的目录路径改变后, 直接回到栈中目录
popd

# Ctrl + z 快速将一个任务放入后台, 临时需要终端处理其他任务后, fg 继续该任务
# 特别是在配置一些文件变量的时候，需要利用终端查看一下路径啥的
top
Ctrl + z
fg

# 忘了给 command 添加 sudo 权限
apt update
# !! 表示上一条命令
sudo !!

# Ctrl + a 快速移动到行首，添加一些指令 sudo 之类的
# Ctrl + e 快速移动到行尾，添加一些内容
# Ctrl + u 快速删除整行命令
# Ctrl + p 快速选择历史命令
# 上下方向键可以快速查看历史命令

# 查看历史命令 每条执行的指令有一个 number 编号
history
# !number_command
!42

sudo apt install cmatrix
cmatrix
# F11 开启/关闭 全屏

# Ctrl + Shift + [+] 快速增大终端字体
# Ctrl + [-] 快速减小终端字体
reset # 恢复终端

sudo apt update; sudo apt install build-essential
# 两个指令中间是否相关依赖 
sudo apt update && sudo apt install build-essential

mount | column -t

```

[Wei Li Blog](https://2694048168.github.io/blog/)