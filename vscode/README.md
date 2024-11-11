# VSCode 使用技巧以及插件推荐

> [Geek for VSCode](https://geek-docs.com/vscode/vscode-tutorials/what-is-vscode.html)

> 详细配置请查看 [VSCode_config.md](VSCode_config.md)

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
- Code Spell Checker; 源代码单词的拼写检查，便于变量名, 帮助提高代码的可读性和质量
- Code Translate; 源代码的单词实时翻译，便于理解
- Path Intellisense; 智能提示并补全文件路径
- Python Microsoft; 提供智能提示和补全
- Remote Development(SSH and WSL); 远程开发和链接服务器
- 可以利用 VSCode 和 PyCharm 的 SSH 进行远程连接进行开发
- Better Comments 是一个用于VSCode的插件, 帮助开发者通过不同颜色和样式来增强代码注释的可读性和可视化效果; 其主要作用包括: 注释分类、提高可读性、自定义标签等

```C++
// TODO: 用于待办事项
// ! 用于重要或警告信息
// ? 用于疑问或需要确认的内容
// * 用于强调或重要说明
// 其他普通注释
```

- VSCode属性配置设置: Indent Rainbow; Indenticator; Trailing Spaces; show spaces;
- Color Highlight(naumovs.color-highlight): 插件的作用是自动检测代码中的颜色值(如十六进制、RGB、RGBA、HSL 等), 并在编辑器中直接显示相应的颜色背景, 使得开发者可以更直观地识别和调整颜色配置
- Color Info(bierner.color-info) 的作用是在代码中显示颜色值的实时预览，方便设计和调试
- koroFileHeader(OBKoro1.korofileheader) 主要用于在文件中自动添加和管理头部注释
- TODO Highlights(zerefdev.todo-highlighter) 高亮显示代码中的 TODO、FIXME 等注释。其主要用于自动识别并高亮显示代码中的 TODO、FIXME 等标记，方便快速定位待办事项
- Image Preview(kisstkondoros.vscode-gutter-preview) 主要用于允许用户在编辑器中直接预览图像文件，而无需打开外部查看器，提高工作效率
- 


## vscode 插件推荐
- C++
    - Extension ID: jeff-hykin.better-cpp-syntax 快速提示C++代码
    - Extension ID: ms-vscode.cpptools 微软VSCode的对 C++ 支持
    - Extension ID: hars.CppSnippets C++ 代码片段
    - Extension ID: llvm-vs-code-extensions.vscode-clangd VSCode 中CLangd支持
    - Extension ID: cschlosser.doxdocgen VSCode 中注释格式支持
- Python
    - Extension ID: njpwerner.autodocstring 快速写 Python 注释
    - Extension ID: ms-python.black-formatter 快速对 Python 代码进行格式化
    - Extension ID: ms-python.python 微软VSCode的对 Python 支持
- Utility
    - Extension ID: christian-kohler.path-intellisense 微软VSCode中快速对文件路径智能提示
    - Extension ID: vscode-icons-team.vscode-icons 微软VSCode中各种icon图标支持
    - Extension ID: skacekachna.win-opacity 微软VSCode中设置窗口透明度支持
    - Extension ID: usernamehw.errorlens 微软VSCode中对错误的直接智能静态提示
    - Extension ID: aaron-bond.better-comments 微软VSCode中对注释(特殊符号)的分类颜色智能提示
    - Extension ID: streetsidesoftware.code-spell-checker 微软VSCode中对单词的拼写检查
    - Extension ID: w88975.code-translate 微软VSCode中对单词的选中翻译
- CMake
    - Extension ID: twxs.cmake 微软VSCode中CMake支持
    - Extension ID: josetr.cmake-language-support-vscode 微软VSCode中CMake语言的支持
    - Extension ID: ms-vscode.cmake-tools 微软VSCode的CMake状态栏工具按钮
- Git
    - Extension ID: eamodio.gitlens 微软VSCode中对Git的可视化支持
    - Extension ID: donjayamanne.githistory 查看git提交日志
- Remote
    - Extension ID: ms-vscode-remote.remote-wsl 微软VSCode中对WSL的支持
    - Extension ID: ms-vscode-remote.remote-ssh 微软VSCode中对SSH远程连接支持
    - Extension ID: ms-azuretools.vscode-docker 微软VSCode中对Docker连接支持
- Themes
    - Extension ID: dracula-theme.theme-dracula
    - Extension ID: PKief.material-icon-theme
    - Extension ID: azemoh.one-monokai
    - Extension ID: zhuangtongfa.Material-theme
    - Extension ID: ahmadawais.shades-of-purple
    - Extension ID: Equinusocio.vsc-material-theme
    - Extension ID: Equinusocio.vsc-material-theme-icons


## About Author

### Talk is cheap, show me the code.
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;——Linus Torvalds

### 掌中星辰转日月，手心苍穹天外天。
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;——云主宰苍穹

### Stay Hungry, Stay Foolish.
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;——Steve Jobs

--------------------------------------------------------------------------------

- Mail：2694048168@qq.com
- GitHub: https://github.com/2694048168/
- Gitee：https://gitee.com/weili_yzzcq/

--------------------------------------------------------------------------------
