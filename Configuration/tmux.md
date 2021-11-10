# tmux

```bash
# 0. install tmux
sudo apt install tmux

# 1. configure file
touch ~/.tmux.conf

# 2. prefix keyboard
Ctrl + b

# 3. command help
Ctrl + b, +?
```

```bash
# tmux configure file
# tmux status line
# 重新加载配置文件
# bind-key R source-file ~/.config/tmux/.tmux.conf
# bind-key R source-file ~/.tmux.conf
# display-message "   Config successfully reloaded"

# 默认情况下，tmux 中使用 vim 编辑器，文本内容的配色和直接使用vim时有些差距，此时需要开启256 colors的支持
set-option -g default-terminal "tmux-256color"

set-option -g status-utf8 on # 状态栏支持utf8

set-option -g status-bg black # 设置状态栏背景黑色
set-option -g status-fg yellow # 设置状态栏前景黄色
set-option -g status-style "bg=black, fg=yellow" # 状态栏前景背景色

# 全局设置 tmux 状态栏位置
# set-option -g status-position top
set-option -g status-position bottom

# 全局设置 tmux 状态栏的前景和背景颜色
set-option -g status-style bg=black, fg=white

# 设置自动重命名会话名
set-option -g automatic-rename on

# 设置 tmux 状态栏的左侧
# 左侧字符占据的长度
set-option -g status-left-length 20
# set-option -g status-left '#(echo Hello WeiLi)'
# 显示会话名
set-option -g status-left '#[fg=colour140]#(echo "Session: )"#[fg=colour130]#{session_name}'

# tmux 状态栏中间调整
set-option -g status-justify centre

# 设置 tmux 状态栏的右侧
set-option -g status-right '#(whoami)#(date)'
# 时间 1 秒更新一下
set-option -g status-interval 1

set-option -wg window-status-format " #I #W " # 状态栏窗口名称格式
set-option -wg window-status-current-format " #I:#W#F " # 状态栏当前窗口名称格式(#I：序号，#w：窗口名称，#F：间隔符)
set-option -wg window-status-separator "" # 状态栏窗口名称之间的间隔
set-option -wg window-status-current-style "bg=red" # 状态栏当前窗口名称的样式
set-option -wg window-status-last-style "fg=red" # 状态栏最后一个窗口名称的样式

set-option -g message-style "bg=#202529, fg=#91A8BA" # 指定消息通知的前景、后景色

```