### Visual Studio(VS) 配置远程 Linux 开发环境

#### 远程 Linux 配置

```shell
# Step1. install base-develop toolchain
# openssh-server、g++、gdb 和 make. 仅CMake项目需要 ninja-build
sudo apt install gcc g++ gdb gdbserver make
sudo apt install cmake ninja-build

# Step2. install ssh tool and config
# https://ubuntu.com/server/docs/openssh-server
sudo apt install openssh-server

# Step3. check the remote Linux IP 
ip address
ip addr
ip a
# or install net tool
sudo apt install net-tools
ifconfig
```

![Linux Develop](./images/LinuxDevelop.png)
![SSH Status](./images/SSH_Status.png)

#### Visual Studio(VS) 配置

- **Step1.** Visual Studio Installer update Linux-develop
![Visual Studio Installer](./images/VSInstaller.png)
- **Step2.** Visual Studio Config the setting
![Visual Studio Config](./images/VSConfig.png)
- **Step3.** Visual Studio SSH Status
![Visual Studio SSH](./images/VSSSH.png)

#### Visual Studio(VS) 开发

- **Step1.** Visual Studio Develop
![Visual Studio Project](./images/VSIntell.png)
- **Step2.** Visual Studio Create Linux Project
![Visual Studio Project](./images/VSCreate.png)
- **Step3.** Visual Studio Intellisense
![Visual Studio Project](./images/VSIntellince.png)
- **Step4.** /home/weili/projects/ 远端Linux生成程序和代码位置
