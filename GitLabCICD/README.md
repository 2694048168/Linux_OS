## GitLab setup the remote source code repo. and config the CI-CD pipeline 

> GitLab is the leading DevSecOps platform.

### Step
1. 下载 GitLab 并安装
    - [GitLab mirror download](https://mirrors.tuna.tsinghua.edu.cn/gitlab-ce/)
    - 根据自己的主机操作系统进行选择下载对应的 GitLab-ce
    - 通过命令进行安装该软件 GitLab-ce
    - 浏览器端以root, 并设置的新的密码
    - 配置 GitLab 一些属性设置, 创建群组和项目仓库, 邀请并管理成员
2. 配置 GitLab以及邮件通知服务
    - etc/gitlab/gitlab.rb 配置文件内修改 Email 相关信息
    - 浏览器端root登录, 编辑个人资料里面的邮件信息
3. 下载安装并注册 GitLab Runner
    - [GitLab Runner mirror download](https://mirrors.tuna.tsinghua.edu.cn/gitlab-runner/)
    - GitLab Runner 的大版本最好与 GitLab 版本保持一致
    - GitLab Runner(17.4.0) && GitLab(17.4.2)
    - [GitLab Runner 命令说明](https://docs.gitlab.com/runner/commands/)
4. 注册 Runner 类型
    - [注册 runner 帮助文档](https://gitlab.cn/docs/runner/register/)
    - Shared Runner: 可用于 GitLab 实例中所有群组和项目
    - Group Runner: 可用于群组中的所有项目和子项目
    - Project Runner: 与特定项目关联, 项目 Runner 只用于一个项目
5. Runner-token 获取
    - Shared Runner: 
        - 浏览器界面点击 [Admin] ---> [CI/CD] ---> [Runner] 
        - ---> [新建实例 runner]旁边的..., 复制token即可;
    - Group Runner: 
        - 浏览器进入项目仓库 [Setting] ---> [CI/CD] ---> [Runner]
        - ---> [Expand] 群组Runner 点击跳转请转到群组的 Runners 页面 
        - ---> [新建群组 runner]旁边的..., 复制token即可;
    - Project Runner: 
        - 浏览器进入项目仓库 [Setting] ---> [CI/CD] ---> [Runner]
        - ---> [新建项目 runner]旁边的..., 复制token即可;
6. CI/CD and DevOps
    - DevOps: Development(开发)和 Operations(运维), 代表的理念和实践
    - Continuous Integration --> Continuous Delivery --> Continuous Deployment 
    - 持续集成 ---> 持续交付 ---> 持续部署 
    - GitLab 配置 CI/CD ---> Pipeline and Runner ---> 'gitlab-ci.yml' config file 
    - GitLab 使用 webhooks 配置钉钉/企业微信做消息通知, 同时邮件通知 
6. Git and 开发流程管理
    - Git basic operators for source code version control
    - Git Commit Message 规范
    - Branch manager and project pipeline: main/develop/features/hotfix/test branches
    - Pull Request(**PR**) for GitHub or Merge Request(**MR**) for GitLab to merge branch
    - Cooperative development and merge with **conflicts** and **Resolve** it
    - 合并提交(保证远程仓库主分支的整洁性和可溯性): using git rebase to merge commits
    - 推荐项目必须所有开发者使用同一份源代码格式管理规范, 如 .clang-format, 避免合并代码时候diff
    - 推荐项目必须所有开发者使用同一种Git commit提交规范, 如 Angular 规范, 避免后续回溯问题和过程难以维护
    - [Git Commit Message 规范](https://konglingfei.com/onex/convention/commit.html)
    - GitLab 做项目发布, 通过打标签 Tag and Release 发布对外的应用程序, 注意版本号规范
    - [版本号规范](https://konglingfei.com/onex/convention/version.html)
    - 接口 API 命名规范: 驼峰命名法(serverAddress), 蛇形命名法(server_address)和脊柱命名法(server-address)


### Commands Tricks

```shell
# 查看当前主机服务器的 Linux-Ubuntu 版本信息
lsb_release -a
# -------- output info --------
# No LSB modules are available.
# Distributor ID: Ubuntu
# Description:    Ubuntu 22.04.5 LTS
# Release:        22.04
# Codename:       jammy
# ------------------------------------

# 查看当前主机服务器的 Linux-Ubuntu CPU架构信息
uname -m
# -------- output info --------
# x86_64
# -----------------------------

# -------- scp command --------
scp local_file remote_username@remote_ip:remote_folder 
scp -r local_folder remote_username@remote_ip:remote_folder 

scp remote_username@remote_ip:remote_folder/remote_file /local_folder 
scp -r remote_username@remote_ip:remote_folder/ /local_folder/ 
# -----------------------------

# 利用下载好的 GitLab-ce 软件包进行安装, 也可以直接通过 apt 包管理器工具直接安装
scp gitlab-ce_17.4.2-ce.0_amd64.deb weili@192.168.188.129:/home/weili
cd /home/weili
sudo apt install gitlab-ce_17.4.2-ce.0_amd64.deb
# recommended use 'dpkg'
sudo dpkg -i gitlab-ce_17.4.2-ce.0_amd64.deb
# -------- output info --------
#      _______ __  __          __
#     / ____(_) /_/ /   ____ _/ /_
#    / / __/ / __/ /   / __ `/ __ \
#   / /_/ / / /_/ /___/ /_/ / /_/ /
#   \____/_/\__/_____/\__,_/_.___/
  
# Thank you for installing GitLab!
# GitLab was unable to detect a valid hostname for your instance.
# Please configure a URL for your GitLab instance by setting `external_url`
# configuration in /etc/gitlab/gitlab.rb file.
# Then, you can start your GitLab instance by running the following command:
#   sudo gitlab-ctl reconfigure
# ------------------------------------------------------------------------

# 成功安装 GitLab 后, 根据提示信息, 修改配置文件并生效配置文件
sudo vim /etc/gitlab/gitlab.rb
# 建议用 VSCode(root远程连接) 或者其他远程SSH终端终端提供的文本编辑器打开

# -------------- 修改内容, 打开注释或者修改内容即可 ---------------------
external_url 'http://192.168.188.129'

gitlab_rails['smtp_enable'] = true
gitlab_rails['smtp_address'] = "smtp.qq.com"
gitlab_rails['smtp_port'] = 25
gitlab_rails['smtp_user_name'] = "2694048168@qq.com"
gitlab_rails['smtp_password'] = "smtp password" # 邮箱授权码
gitlab_rails['smtp_domain'] = "smtp.qq.com"
gitlab_rails['smtp_authentication'] = "login"
gitlab_rails['smtp_enable_starttls_auto'] = true
gitlab_rails['smtp_tls'] = false
gitlab_rails['smtp_pool'] = false

gitlab_rails['gitlab_email_from'] = '2694048168@qq.com'

gitlab_rails['gitlab_ssh_host'] = '192.168.188.129'

gitlab_rails['gitlab_shell_ssh_port'] = 22
# -------------------------------------------------------------
sudo gitlab-ctl reconfigure
# -------- output info --------
# Running handlers:
# [2024-10-13T00:18:00+08:00] INFO: Running report handlers
# Running handlers complete
# [2024-10-13T00:18:00+08:00] INFO: Report handlers complete
# Infra Phase complete, 582/1606 resources updated in 02 minutes 59 seconds

# Notes:
# Default admin account has been configured with following details:
# Username: root
# Password: You didn't opt-in to print initial root password to STDOUT.
# Password stored to /etc/gitlab/initial_root_password. This file will be cleaned up in first reconfigure run after 24 hours.

# NOTE: Because these credentials might be present in your log files in plain text, it is highly recommended to reset the password following https://docs.gitlab.com/ee/security/reset_user_password.html#reset-your-root-password.

# gitlab Reconfigured!
# -------------------------------------------------------------
# 成功后, 根据提示信息, root 的密码在 24H 后被删除, 首先需要修改 root 密码
# 在浏览器中 输入服务器IP地址, 即可弹出登陆入口, root, 密码在 /etc/gitlab/initial_root_password
# [用户头像] ---> [Preferences] ---> [Password] ---> 将当前密码和修改后密码
# [用户头像] ---> [Preferences] ---> [Localization] ---> [Language] 选择简体中文,然后保存配置退出重新登录即可

# 使用 gitlab-rails 工具测试邮件通知服务是否正常
sudo gitlab-rails console
# 发送邮件进行测试, 需要可以正常连接外网
Notify.test_email('2694048168@qq.com', 'Message Subject', 'Message Body').deliver_now
Notify.test_email('weili_yzzcq@163.com', 'Message Subject', 'Message Body').deliver_now

# 在浏览器中 输入服务器IP地址, 即可弹出登陆入口, root和设置的密码
# [用户头像] ---> [Edit profile] ---> [Email] 然后保存配置退出重新登录即可
# @note: 邮件接受可能存在延时, 不需要重复操作, 避免收到很多邮件信息

# ---------------------------------------------------------------------
# 下载安装并注册 GitLab Runner, 需要一系列的依赖......
scp gitlab-runner_17.4.0-1_amd64.deb weili@192.168.188.129:/home/weili
cd /home/weili
sudo dpkg -i gitlab-runner_17.4.0-1_amd64.deb
# ----------------- OUTPUT INFO -----------------------------------------
# Selecting previously unselected package gitlab-runner.
# (Reading database ... 293361 files and directories currently installed.)
# Preparing to unpack gitlab-runner_17.4.0-1_amd64.deb ...
# Unpacking gitlab-runner (17.4.0-1) ...
# dpkg: dependency problems prevent configuration of gitlab-runner:
#  gitlab-runner depends on curl; however:
#   Package curl is not installed.

# dpkg: error processing package gitlab-runner (--install):
#  dependency problems - leaving unconfigured
# Errors were encountered while processing:
#  gitlab-runner
# ---------------------------------------------------------------------
# 根据输出的错误提示, 可以知道 gitlab-runner 需要 curl 的依赖支持, 用apt/nala先安装 curl
sudo apt install curl -y
sudo nala install curl -y

# 建议使用官方包管理工具软件仓库进行自动安装, 解决依赖问题
sudo dpkg -r gitlab
rm gitlab-runner_17.4.0-1_amd64.deb
# Add the official GitLab repository
curl -L "https://packages.gitlab.com/install/repositories/runner/gitlab-runner/script.deb.sh" | sudo bash
# Install the latest version of GitLab Runner
sudo apt install gitlab-runner
# To install a specific version of GitLab Runner
sudo apt-cache madison gitlab-runner
sudo apt install gitlab-runner=17.4.0-1
# ------------output info -------------------
# Reading package lists... Done
# Building dependency tree... Done
# Reading state information... Done
# Suggested packages:
#   docker-engine
# The following NEW packages will be installed:
#   gitlab-runner
# 0 upgraded, 1 newly installed, 0 to remove and 18 not upgraded.
# Need to get 500 MB of archives.
# After this operation, 568 MB of additional disk space will be used.
# Get:1 https://packages.gitlab.com/runner/gitlab-runner/ubuntu jammy/main amd64 gitlab-runner amd64 17.4.0-1 [500 MB]
# Ign:1 https://packages.gitlab.com/runner/gitlab-runner/ubuntu jammy/main amd64 gitlab-runner amd64 17.4.0-1                               
# Get:1 https://packages.gitlab.com/runner/gitlab-runner/ubuntu jammy/main amd64 gitlab-runner amd64 17.4.0-1 [500 MB]
# Fetched 259 MB in 4min 8s (1,043 kB/s)                                                                                                    
# Selecting previously unselected package gitlab-runner.
# (Reading database ... 293372 files and directories currently installed.)
# Preparing to unpack .../gitlab-runner_17.4.0-1_amd64.deb ...
# Unpacking gitlab-runner (17.4.0-1) ...
# Setting up gitlab-runner (17.4.0-1) ...
# GitLab Runner: detected user gitlab-runner
# Runtime platform                                    arch=amd64 os=linux pid=34757 revision=b92ee590 version=17.4.0
# gitlab-runner: the service is not installed
# Runtime platform                                    arch=amd64 os=linux pid=34764 revision=b92ee590 version=17.4.0
# gitlab-ci-multi-runner: the service is not installed
# Runtime platform                                    arch=amd64 os=linux pid=34784 revision=b92ee590 version=17.4.0
# Runtime platform                                    arch=amd64 os=linux pid=34836 revision=b92ee590 version=17.4.0
# INFO: Docker installation not found, skipping clear-docker-cache
# ----------------------------------------------------------------------------
# 通过输出信息可知, Docker没有安装, gitlab-runner service and gitlab-ci-multi-runner都没有安装
# 不过我们不需要, 和 GitLab 做联合处理, 直接将 Gitlab-runner 注册到 GitLab

# 可以使用镜像的仓库地址, 帮助文档如下:
# https://mirrors.tuna.tsinghua.edu.cn/help/gitlab-runner/
# 启动 Gitlab-runner 并查看信息, 检查是否安装成功
sudo gitlab-runner start
sudo gitlab-runner run
gitlab-runner --version
gitlab-runner -v
# ------------output info -------------------
# Version:      17.4.0
# Git revision: b92ee590
# Git branch:   17-4-stable
# GO version:   go1.22.5
# Built:        2024-09-19T11:11:17+0000
# OS/Arch:      linux/amd64
# -------------------------------------------
gitlab-runner status
# ------------output info -------------------
# Runtime platform arch=amd64 os=linux pid=36267 revision=b92ee590 version=17.4.0
# gitlab-runner: Service is running
# -------------------------------------------
# 交互式注册 runner, 需要 GitLab 服务器所在 rul 和 注册令牌 token
# 在浏览器界面可以拿到 runner-token
gitlab-runner register --url http://192.168.188.129 --registration-token

# 查看参数说明
gitlab-runner register --help

# 无交互式注册 runner
sudo gitlab-runner register \
  --non-interactive \
  --url "http://192.168.188.129/" \
  --registration-token "o8_-271ZEaJa7S6CJdxn" \
  --executor "shell" \
  --tag-list "Shared, Complier-Building" \
  --description "The Shared Runner for Compile and Build" \
  --maintenance-note "Free-form maintainer notes about this runner" \
  --run-untagged="true" \
  --locked="false" \
  --access-level="not_protected"

# ------------output info -------------------
# Runtime platform  arch=amd64 os=linux pid=37490 revision=b92ee590 version=17.4.0
# Running in system-mode.                            
                                                   
# WARNING: Support for registration tokens and runner parameters in the 'register' command has been deprecated in GitLab Runner 15.6 and will be replaced with support for authentication tokens. For more information, see https://docs.gitlab.com/ee/ci/runners/new_creation_workflow 
# Registering runner... succeeded                     runner=o8_-271Z
# Runner registered successfully. Feel free to start it, but if it's running already the config should be automatically reloaded!
 
# Configuration (with the authentication token) was saved in "/etc/gitlab-runner/config.toml"
# ------------------------------------------------------------------------
# 提示注册成功, 但是警告注册方式后续通过 authentication token 方式注册
# 回到浏览器界面, 刷新即可看到注册的 runner

# 首先在浏览器 UI 中创建的 Runner , 然后使用身份验证令牌进行注册, 交互式的注册
# Register with a runner authentication token
sudo gitlab-runner register  --url http://192.168.188.129  --token glrt-mZN1Ptz9q3pusGnQVXyE

# Register with a runner authentication token, 无交互式的注册
sudo gitlab-runner register \
  --non-interactive \
  --url http://192.168.188.129 \
  --token glrt-3zCPb1gRqYrtJw5HRf5v \
  --executor "shell"
# ------------------------------------------------------------------------

```
