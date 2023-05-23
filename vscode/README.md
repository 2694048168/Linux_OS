# VSCode 使用技巧以及插件推荐

> [Geek for VSCode](https://geek-docs.com/vscode/vscode-tutorials/what-is-vscode.html)

## vscode 快捷键 (减少使用鼠标，编写源代码的时候尽量使用键盘)

- [Help] --> [Keyboard Shortcuts Reference]; 即可在浏览器中打开对应操作系统的快捷键文件
- Code Snippets; 源代码片段管理，快捷键入源代码，提高效率
- [File] --> [Preferences] --> [User Snippets]; 
- [Ctrl] + [Shift] + p, 调出命令面板，输入 snippet, 选择对应的语言，参考模板进行自定义代码片段
- [Ctrl] + [Shift] + p, 调出命令面板，输入 screencast, 打开键盘按键回显功能

## vscode 加载和配置

- .vscode 文件夹
- launch.json; 该文件配置 VSCode 如何管理和启动 Debug 代码
- task.json; 该文件配置 VSCode 如何编译源代码
- VSCode 提供了一系列的宏，该宏变量用户灵活处理和配置
- https://code.visualstudio.com/docs/editor/variables-reference

## vscode 技巧

```python
# 利用 miniconda 进行 python 版本的管理和虚拟环境的隔离

# python import packages 导入自己写的功能包 init.py 方法除外
# 直接将项目的根目录添加到系统检索路径中即可 (一定要在需要导入自己功能包之前)
import sys
sys.path.append("./")
from function_packages_dir import function_file_name
# function_file_name.FunctionName 使用方法

# 路径复制, 正斜杠和反斜杠的错误快速更正
# 使用 [Ctrl] + d 将选择添加到下一个查找匹配项，全部匹配后进行一次性更正

# [Ctrl] + [ 快速进行向左缩进
# [Ctrl] + ] 快速进行向右缩进

# Ctrl + Shift + p 快速命令面板
# reload 命令快速重启 vscode
# minimap 命令快速开启/关闭 小地图功能
# zoom 命令快速选择放大/缩小 窗口/字体 功能, 便于演示
# interpreter 命令快速选择 python 解释器环境

# Ctrl + p 快速检索文件名并打开
```

## vscode 主题插件

- Andromeda
- Shades of Purple
- Cobalt2 Theme Official
- Dracula Official
- Halcyon Theme
- Night Owl
- Tokyo Night


## vscode 插件推荐 (插件可以在本地安装，也可以只配置远程服务器的[用于远程开发])

- [VSCode Marketplace](https://marketplace.visualstudio.com/)
- [VSCode Snippets](https://marketplace.visualstudio.com/search?target=VSCode&category=Snippets&sortBy=Relevance)
- [VSCode Themes](https://marketplace.visualstudio.com/search?target=VSCode&category=Themes&sortBy=Relevance)

- Polacode-2020; vscode 输出代码图片, 即见即所得
- vscode-icons; vscode的图标插件, 对文件以及目录显示图标
- translate speaker 翻译朗读者API; 这是一个非常简单好用的翻译-朗读-替换字符串一体化插件，你只需要配置一个接口参数即可
- autoDocstring; autoDocstring - Python Docstring Generator
- advanced-new-file; Create files anywhere in your workspace from the keyboard(Ctrl+shift+p)
- Shades of Purple; VSCode 一款不错的全局颜色主题
- Doxygen Documentation Generator; Doxygen 风格代码注意模板
- Bracket Pair Colorizer; 彩色括号匹配，便于编辑和查阅源代码
- C/C++ Microsoft; 智能提示和调试
- CMake Microsoft; 提供 CMake 语言支持和提示
- CMake Tools Microsoft; 提供将 CMake 命令和可视化按钮进行关联
- Code Spell Checker; 源代码单词的拼写检查，便于变量名
- Code Translate; 源代码的单词实时翻译，便于理解
- Path Intellisense; 智能提示并补全文件路径
- Python Microsoft; 提供智能提示和补全
- Remote Development(SSH and WSL); 远程开发和链接服务器
- 可以利用 VSCode 和 PyCharm 的 SSH 进行远程连接进行开发


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
