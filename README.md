# Wallpaper
把 h5 网页做成 Windows 动态壁纸。Make html to windows wallpaper，html、c++ and QT
### 文章链接
[使用html5/c++实现windows桌面壁纸](https://zhuanlan.zhihu.com/p/37877070)
### 原理
- 窗口位置（handle）
![image](./images/source_1.png)
- 发生信息（windows message）
![image](./images/source_2.png)
### 设置（config）
- 支持多屏延展
- 本地路径加载页面
- URL加载页面
### 局限性（limit）
- 不兼容 win8
- 无法与 h5页面交互
- 占用资源较大
### 优化方案
- 弃用QT,包括 WebEngine,更轻量级的 chrome 内核
- windows api 实现底层交互




