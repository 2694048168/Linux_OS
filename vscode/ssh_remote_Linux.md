# SSH 远程登入服务器，图形化远程控制，文本传输和辅助脚本

## SSH 安全登入

```shell
# step 1. Linux 服务器安装 SSH 服务程序 并打开 ssh 服务的端口 22/21
sudo apt install openssh-server

# step 2. 查看服务器的 ip 地址
ip addr

# step 3. 使用 ssh 命令进行终端登入
ssh user_name@ip_linux_server
```

## 图形化远程

- TeamViewer 安装在 Linux 服务器和自己的客户端，利用该软件进行图形化远程

## SSH 文本传输

```shell
# 远程传输文件
# 从本地传输文件到服务器
scp /local_dir/files user_name@ip_linux_server:~/linux_dir
# 从服务器传输文件到本地
scp user_name@ip_linux_server:~/linux_dir /local_dir/files 
```

## SSH 脚本辅助

- 利用 shell 脚本完成在服务器端的流水线任务处理
- 利用 python 脚本完成一些特定的任务批处理
- Tmux 可以实现终端和会话的分离

## About Author

### Talk is cheap, show me the code.
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;——Linus Torvalds

### 掌中星辰转日月，手心苍穹天外天。
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;——云主宰苍穹

### Stay Hungry, Stay Foolish.
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;——Steve Jobs

--------------------------------------------------------------------------------

- Mail：2694048168@qq.com
- Weibo：云主宰苍穹
- GitHub: https://github.com/2694048168/
- Gitee：https://gitee.com/weili_yzzcq/

--------------------------------------------------------------------------------
