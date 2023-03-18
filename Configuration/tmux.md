## tmux

![tmux](https://github.com/tmux/tmux/raw/master/logo/tmux-logo-medium.png?raw=true)

> 主要是分离会话和终端的功能, 还有就是分屏操作. 用户通过命令行的终端窗口,与计算机的这种临时的交互, 称为一次会话session; 会话时, 窗口与其中启动的进程是连在一起的, 即关闭窗口, 会话结束, 同时会话内的进程也会随之终止, 不管有没有运行完. 这对于在服务器上通过SSH登录并执行命令,突发意外(ssh断联, 网络中断, 想结束终端和关闭电脑), 导致SSH会话终止, 同时里面的进程也随之消失了. Tmux就是为了解决这个问题, 实现会话与窗口可以解绑分离; 窗口关闭时, 会话并不终止, 而是继续运行, 等到需要的时候, 再让会话绑定窗口.

**sources linker**
- [tmux wiki](https://github.com/tmux/tmux/wiki)
- [Tmux 使用教程](https://www.ruanyifeng.com/blog/2019/10/tmux.html)
- Tmux 的前缀键(prefix keyboard)默认是 'Ctrl + b', 配置文件里面可以对此进行修改
- [Oh my tmux](https://github.com/gpakosz/.tmux)
- [Vim](https://github.com/vim/vim)
- [NeoVim](https://github.com/neovim/neovim)
- 如何利用 NeoVim 打造现代终端代码 IDE
- [LunarVim](https://github.com/lunarvim/lunarvim)
- [SpaceVim](https://github.com/SpaceVim/SpaceVim/)


### Quick Start

```bash
# Step 0. install tmux
sudo apt update && sudo apt upgrade
sudo apt install tmux

sudo nala update && sudo nala upgrade
sudo nala instal tmux

# 查看 tmux 版本
tmux -V

# Step 1. 启动 tmux
# 默认设置 session 的编号为 '0'
tmux

# Step 2. 查看帮助信息
Ctrl + b, +?
# enter 'q' or 'Esc' t退出查看

# Step 3. 退出 tmux
exit
# or enter 'Ctrl + d'
```

### Session Management

```bash
# 新建一个 session, 并设置 session 的名称为 'training'
tmux new -s training

# and then training model on Server
python train.py

# 分离会话, 此时模型的训练依然需要进行
# or enter 'Ctrl + b', 'd'
tmux detach

# 查看当前所有 session
tmux ls
tmux list-session

# 接入已有的会话 'training'
tmux attach -t training

# -------------------------
# kill session 'training'
tmux kill-session -t training

# tmux switch 命令用于切换会话
tmux new -s model
tmux new -s task
tmux
tmux switch -t task
tmux switch -t model

# 分屏需要理解的概念, 基本用不到, 很多终端都支持这个功能
# Session | Window | Pane
```

### Oh-my-tmux

- 配置定制, ^_^, 开箱即用就是最简单最好的
- 同时在 tmux 中可以配置 vim/NeoVim/SpaceVim/LunarVim
