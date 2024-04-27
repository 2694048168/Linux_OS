![Linux Logo](../LinuxOS.jpg)

> Ubuntu使用过程中常用的配置和命令

### 首次安装的基本配置
```shell
# 0. 设置终端的大小和位置
# 打开一个新的终端窗口, 在 preference 设置字体大小和终端大小
gsettings set org.gnome.mutter center-new-windows true
# 按回车键 即可设置所有打开应用均默认在屏幕中间

# 1. 设置 root 密码, 输入并确定即可(默认不回显)
sudo passwd
# 切换到 root 用户, 测试密码
su root

# 2. 更换软件源到国内镜像后, 更新软件源列表信息本地索引
sudo apt update

# 3. 安装 ssh
sudo apt install openssh-server
# 配置SSH
sudo vim /etc/ssh/sshd_config
sudo gedit /etc/ssh/sshd_config
# 找到下面内容, 禁止 root 用户远程登录
# PermitRootLogin yes
# PasswordAuthentication yes

# 设置开机自启动
sudo systemctl enable ssh
sudo systemctl is-enabled ssh
# 查看SSH服务状态
sudo systemctl status ssh

# 4. 查看IP, 远程ssh连接
ip addr
ssh weili@192.168.188.129
# 输入 yes 授权, 然后输入该用户的密码即可登录
ssh root@192.168.188.129

# 根据需要设置防火墙
sudo ufw allow ssh
```

### 包管理工具

- [**nala**](https://gitlab.com/volian/nala)
- [**man package nala**](https://manpages.ubuntu.com/manpages/noble/en/man8/nala.8.html)
- [**man package apt**](https://manpages.ubuntu.com/manpages/noble/en/man8/apt.8.html)

```shell
# apt 更换为 nala
# 1. 安装 nala
sudo apt update && sudo apt install nala

# 2. nala 选择最佳镜像源, 需要等待一会测试
sudo nala fetch
# 根据索引, 以空格方式输入想要的镜像源即可

# 3. 利用 nala 并行下载更新所有软件
sudo nala update && sudo nala upgrade

# 利用 dpkg 管理 deb 格式
sudo dpkg -i xxx.deb  # 安装 deb 格式的软件
sudo dpkg -r xxx      # 卸载 deb 格式安装的软件
```

### shell

- [**zsh**](https://www.zsh.org/)
- [**on my zsh**](https://ohmyz.sh/)
- [**on my zsh Themes**](https://github.com/ohmyzsh/ohmyzsh/wiki/Themes)

```shell
# 将默认shell工具 bash 配置为 zsh
# 1. 检查当前可用的 shell
cat /etc/shells
# bash 的配置文件 .bashrc

# 2. 查看当前使用的shell
echo $SHELL

# 3. 安装 zsh shell
sudo nala install zsh -y

# 4. 查看 shell 版本 切换默认使用 zsh
zsh --version
sudo chsh -s $(which zsh)
# root 用户默认使用 bash
sudo chsh -s $(which bash) root
sudo usermod -s /bin/zsh weili
sudo usermod -s $(which zsh) weili

# 注销当前用户重新登录, 验证当前默认 Shell
# 再次打开终端, 会选择生成配置文件 .zshrc
# 5. 安装 git 工具
sudo nala install git
git --version

# 6. 安装 oh-my-zsh, 配置 zsh
sh -c "$(wget https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh -O -)"
sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# 7. 下载 zsh-syntax-highlighting 语法高亮插件
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh}/plugins/zsh-syntax-highlighting

# 下载 zsh-autosuggestions 自动提示插件
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions

# 配置 .zshrc文件 更换默认主题 alanpeabody
vim ~/.zshrc
gedit ~/.zshrc
# 添加内容
plugins=(git zsh-syntax-highlighting zsh-autosuggestions)

# 配置生效
source ~/.zshrc
```

### VSCode 终端远程连接
- [**Windows Terminal and on my posh**](https://ohmyposh.dev/)
```shell
# Windows 安装 Terminal + on my posh
# 1. VSCode 安装插件, Extension ID
# ms-vscode-remote.remote-ssh

# 2. 选择插件加号, 即可添加ssh配置到文件
ssh weili@192.168.188.129

# 3. 选择插件的设置按钮, 即可查看远端ssh配置
# 4. 刷新按钮点击, 即可刷新添加的ssh远端, 连接输入用户密码
# 5. 第一次连接会在远端安装 VSCode server, 需要点时间
# 6. 连接成功后, VSCode 左下角有明显标志
# 7. 需要在远端开发, 注意VSCode 的本地插件和远端插件的区别
```
