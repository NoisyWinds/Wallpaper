# Wallpaper
把 h5 网页做成 Windows 动态壁纸。Make html5 to windows wallpaper，html、c++ and QT

### 文章链接
[使用html5/c++实现windows桌面壁纸](https://zhuanlan.zhihu.com/p/37877070)
### 原理
1. 窗口位置（handle）
![image](./images/source_1.png)
2. 发送信息（windows message）

<br>

![image](./images/source_2.png)

<br>


### 发布版下载（releases）

[https://github.com/ThomasHuai/Wallpaper/releases](https://github.com/ThomasHuai/Wallpaper/releases)

### 演示 （demo）

<br>

![image](./images/1.gif)
自带粒子效果

<br>

![image](./images/2.gif)
three.js demo

<br>

![image](./images/3.gif)
three.js demo

<br>

### 设置（config）
- 支持多屏延展
- 本地路径加载页面
- URL加载页面
- 浏览器内核为 chrome，支持 WebGL
### 局限性（limit）
- 不兼容 win8
- 无法与 h5页面交互
- 占用资源较大
### 优化方案
- 弃用QT,包括 WebEngine,更轻量级的 chrome 内核
- windows api 实现底层交互




