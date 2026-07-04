# Git Quick Tutorial

<div align="center">
  <p><strong>Git Quick Start Tutorial from Scratch for Beginner</strong></p>
</div>

![git](https://git-scm.com/images/logo@2x.png)

> [!NOTE]
>
> **安装Git**：[Git Download](https://git-scm.com/install/windows)
>
> **Git版本选型**：**建议安装最新版本**
> 
```shell
# 查看 Git 版本, 检验是否正常安装
git --version
# output: git version 2.55.0.windows.1
```
>

## 配置 Git
> 安装后需要告诉 Git 基本信息, Git 每次提交都会记录作者信息, 包括用户名和邮箱

```shell
# 配置用户名
git config --global user.name "你的名字"
# git config --global user.name "Ithaca"

# 配置邮箱
# GitHub or GitLab or 公司的远程Git托管平台 配合使用, 建议这里填写 对应 账号绑定的邮箱
git config --global user.email "你的邮箱"
# git config --global user.email "weili_yzzcq@163.com"

# 查看 Git 所有配置信息
git config --list
# >>> output:
# user.name=Wei Li
# user.email=weili_yzzcq@163.com
# diff.tool=vscode
# difftool.vscode.cmd=code --wait --diff $LOCAL $REMOTE
# merge.tool=vscode

# 单独查看配置
git config user.name
git config user.email

# 配置默认分支名
# git init 创建仓库时, 默认分支就是 main
git config --global init.defaultBranch main

```

## Git 核心概念
> 快速了解 Git 核心概念, 便于后续快速操作和与人交流沟通

- 仓库 repository
> 普通文件夹变成 Git 仓库后，里面会多一个隐藏目录 **.git** 成为 Git 管理的项目目录, 即为 repository;  **.git** 目录保存了 Git 的版本历史、分支、提交等信息

- 提交 commit
> 一次提交就是项目在某个时刻的快照, **git add** 是选择要保存哪些变化; **git commit** 是真正保存一个存档

- 分支 branch
>
> [!IMPORTANT]
>
> 分支是一条独立的开发线,分支可以在不影响主线的情况下开发新功能
>
> main：稳定主分支。
>
> feature/logger：开发日志功能的分支
>
> fix/navbar-bug：修复导航栏问题的分支
>

- 远程仓库 remote repository
>
> [!IMPORTANT]
> 
> 本地仓库在你电脑里, 远程仓库在服务器上, 如 **GitHub/Gitee/GitLab** 等公共的Git代码托管平台
> 
> **常见操作**：
>
> push：把本地提交推送到远程。
>
> pull：把远程更新拉到本地。
> 
> clone：从远程复制一份仓库到本地
>

## 创建本地仓库
```shell
# 新建项目目录
mkdir testRepo
cd testRepo

# 初始化 Git 仓库
git init
# output: Initialized empty Git repository in ...

# 查看状态
git status
git status -c

```

### 工作区域和文件状态
>
> [!IMPORTANT]
> 
> 工作区 ---> Working Tree ---> 正在编辑的文件
>
> 暂存区 ---> Staging Area / Index --->	准备进入下一次提交的内容
> 
> 本地仓库 --->	Repository ---> 已经提交保存的历史

>
> [!IMPORTANT]
>
> Untracked	---> 新文件, Git 还没有追踪
> 
> Modified --->	文件被修改了, 但还没暂存
> 
> Staged ---> 文件已经暂存, 准备提交
> 
> Committed	---> 文件已经提交到本地仓库
> 

### 状态变化流程
> 一个文件从新建到提交, 大致经历
```
新建文件
  -> Untracked
git add 文件
  -> Staged
git commit
  -> Committed
修改文件
  -> Modified
git add 文件
  -> Staged
git commit
  -> Committed
```

### 添加和提交文件
```shell
# git add 的作用是把文件变化放入暂存区
# 它不是提交 它只是告诉 Git：下一次提交我要包含这些变化
# --------------
# 添加单个文件
git add README.md
# 添加多个文件
git add main.cpp app.hpp app.cpp
# 添加当前目录所有变化
# 要先检查 git status
git add .

# ===================================
# git commit 会把暂存区内容保存为一次提交
# git commit -m "初始化项目" -m 后面是提交信息
# 提交信息应该简短说明这次做了什么
git commit -m "修复登录按钮样式"

# -----------------------
# 为什么要先 add 再 commit
# 因为 Git 允许你选择哪些变化进入下一次提交
# 例如你同时修改了：

# README.md
# index.cpp
# style.cpp

# 但你只想提交 README：

# git add README.md
# git commit -m "更新 README"

# 剩下两个文件仍然留在工作区

```

### 查看历史和差异
```shell
git log
# 输出会包含:
# commit id
# 作者
# 日期
# 提交信息

# output:
commit 4b9e46ac348084abb5868a20b21cb7880b9d7f58 (HEAD -> main, tag: v1.4.0)
Author: Wei Li <weili_yzzcq@163.com>
Date:   Thu Jul 2 22:54:18 2026 +0800

    feat: Version information and authorization function


# ----------
# 简洁查看历史
git log --oneline
git log --oneline -n12

# 图形化查看分支历史, 该命令在查看很多分支时很有用
git log --oneline --graph --all

# ==========
# 查看未暂存修改, 显示工作区中还没有加入暂存区的变化
git diff

# 查看已暂存修改, 显示已经 git add，但还没有 git commit 的变化
git diff --cached

```

### 撤销修改与 git reset

>
> [!IMPORTANT]
> 
> 撤销前先执行 git status, 看清楚文件在哪里!!!
>

```shell
# 撤销工作区修改, !!!注意：这个操作会丢弃工作区修改!!!
# 如果修改了一个文件, 但还没有 git add, 想丢弃修改
git restore filename

# 撤销暂存, 如果已经执行 add, 想把它从暂存区拿出来
# !!!这个命令不会删除你的文件修改, 只是取消暂存!!!
git restore --staged filename

# -------------------------------------------
# HEAD 表示当前所在的提交
# git reset 经常用于移动 HEAD 指针 <三个常见模式>
# git reset --soft	-->移动 HEAD 指针 --> 不改暂存区 --> 不改工作区
# git reset --mixed	-->移动 HEAD 指针 --> 撤销暂存区 --> 不改工作区
# git reset --hard	-->移动 HEAD 指针 --> 撤销暂存区 --> 撤销工作区
```

### **.gitignore** 忽略文件
> .gitignore 是一个文本文件, 用来告诉 Git 哪些文件不需要被追踪
常见不应该提交的内容：
- 依赖目录，如 node_modules/
- 构建产物，如 dist/
- 系统文件，如 .DS_Store
- 密钥文件，如 .env
- 日志文件，如 *.log

>
> [!IMPORTANT]
> 
> 已经被 Git 追踪的文件怎么办

如果一个文件已经被提交过, 后来才加入 **.gitignore**, Git 仍然会继续追踪它 要停止追踪, 但保留本地文件或者目录
```shell
git rm --cached filename
git commit -m "停止追踪 filename 文件"

git rm -r --cached folder
git commit -m "停止追踪 folder 目录"
```

> [!NOTE]
>
> **测试GitHub配置**：
> 
```shell
# 测试 SSH 连接
ssh -T git@github.com
# Are you sure you want to continue connecting?

# output:
# git@github.com: Permission denied (publickey).
```
>

### 关联本地仓库和远程仓库
```shell
# 查看当前远程仓库
git remote -v
# output:
# origin  https://github.com/2694048168/Linux_OS.git (fetch)
# origin  https://github.com/2694048168/Linux_OS.git (push)
# origin_gitee    https://gitee.com/weili_yzzcq/linux_-os.git (fetch)
# origin_gitee    https://gitee.com/weili_yzzcq/linux_-os.git (push)

# 添加远程仓库, origin 是远程仓库的默认名字
git remote add origin git@github.com:用户名/仓库名.git

# 推送到远程仓库, 如 GitHub
git push -u origin main
# push：推送本地提交到远程
# origin：远程仓库名字
# main：本地分支名
# -u：建立本地 main 和远程 main 的跟踪关系

# 如果默认分支不是 main,可以修改当前分支名称
git branch -M main

# 克隆远程仓库
git clone git@github.com:用户名/仓库名.git
# --recursive 表示递归 clone, 可能该仓库包含其他仓库
git clone --recursive git@github.com:用户名/仓库名.git

```

## 分支基础
```shell
# 切换并创建一个功能分支
git switch -c feature/logger

# 查看分支, 当前分支前面会有 *
git branch
git branch -a

# 创建分支, 只是创建，不会切换过
git branch hotfix/login_bug

# 删除分支
git branch -d hotfix/login_bug
# 强制删除未合并分支, 注意：-D 更危险
git branch -D feature/logger

# 合并分支, 合并 logger 功能分支
git switch main
git merge feature/logger

# !!! fast-forward 合并
# 如果 main 没有新的提交，Git 可能会执行 fast-forward
# 可以理解为：main 指针直接向前移动到 feature/login 的位置
# 这种合并不会产生新的 merge commit

# !!!普通 merge commit
# 如果两个分支都有新提交，Git 需要创建一个合并提交
# 这种提交会记录：
# 来自主分支的历史
# 来自功能分支的历史
# 合并的结果

# !!!合并后删除分支
git branch -d feature/logger
# 远程分支删除
git push origin --delete feature/logger
```

## 合并冲突

> [!WARNING]
>
> 当两个分支修改了同一个文件的同一部分，Git 不知道该保留谁，就会产生冲突
>
```
冲突文件长什么样#
打开 message.txt，可能看到：

<<<<<<< HEAD
hello from main
=======
hello from feature a
>>>>>>> feature/a
含义：

<<<<<<< HEAD 到 =======：当前分支内容。
======= 到 >>>>>>> feature/a：要合并进来的分支内容。
```
>

## 回退、revert 与 rebase
- git reset --> 是(改写历史记录) --> 本地提交还没分享给别人
- git revert --> 否(改写历史记录) --> 已经推送到远程,别人可能已经拉取

### 使用 revert 安全撤销提交#
```shell
# 查看历史：
git log --oneline
# 假设要撤销某个提交：
# git revert 提交ID
git revert a1b2c3d
# Git 会创建一个新的提交，用来抵消之前那个提交的修改
# 好处：不破坏公共历史; 团队协作更安全
```

### rebase 是什么
> rebase 可以把一串提交(commit) **搬到** 另一个基底上
```shell
# main:    A---B---C
# feature:     \---D---E

git switch feature
git rebase main
```

> [!WARNING]
>

```
# main:    A---B---C
# feature:         \---D'---E'
# 注意 D 和 E 变成了 D' 和 E', 这说明提交 ID 变了

# rebase 的优点
# - 历史更直
# - 查看 log 更清晰
# - 功能分支合并前可以整理提交
```

> [!WARNING]
>

```
# rebase 的风险
# - 不要随便 rebase 已经推送并且多人使用的公共分支
# - 因为 rebase 会改写提交历史，可能导致别人本地历史和远程历史不一致
# 推荐原则：
# 自己本地的 feature 分支可以 rebase，公共 main 分支不要 rebase

# pull --rebase
# 如果你本地有提交，远程也有新提交，可以用
git pull --rebase
# 它会先拉取远程更新，再把你的本地提交重新放到最新代码后面
```
