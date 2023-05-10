# OpenGL_demo

参考：蓝桥网课：太阳系行星系统 https://www.lanqiao.cn/courses/558
主要梳理概念，不写大量的代码（可能会显得非常臃肿），代码打包放到github上。
闲得无聊逛sh聚聚的博客，发现了一个很好的openGL学习网站，挂一下：https://learnopengl-cn.github.io/
顺便挂一下sh聚当时的记录：https://www.kirito.info/learn-opengl-env/

# 写在前面
1. 通过windows下的openGL实现简单的绘图和动画。
2. 利用vs2022开发。

openGL包含了很多渲染函数，但他们是独立于操作系统和窗口系统的，本身并没有包含创建窗口或者读取键鼠的函数，因此需要额外使用GLUT（openGL Uitlity Toolkit），负责处理操作系统的调用，使用GLUT可以屏蔽操作系统的差异，可以实现跨平台。
windows开发，可以自己通过相关安装openGL的博客去自行安装，也可以通过vs2022的解决方案中的`管理NuGet程序包`搜索`nupengl.core`安装，vs2022会自动配置相关环境。
# 项目介绍
main函数：初始化窗口参数，定义回调函数。

star类：
- 定义星星的基本参数，包括材质，位置，速度等信息。
- 提供展示图像和更新参数的两个接口。

solarSystem类：
- 定义太阳系内的常见天体参数（几个行星，卫星和太阳）。
- 提供显示，更新窗口和监听键盘信息的接口。

通过实现star类计算星球相对位置。
通过solarSystem类定义相机信息，调用star中的show和update方法。同时通过监听键鼠信息来调整相机的位置。
# 细节方法
openGL提供的方法都是`glutXxx()`方法，因此很容易就能分辨出来那些方法是用的库函数。
## main函数
初始化窗口信息和参数，定义显示和更新的回调函数。
主要包括
- 初始化窗口
	- glutInit() 用来初始化GLUT库，获取main函数里面的两个参数，
	- glutInitDisplayMode() 用来定义窗口的显示模式，包括颜色显示，缓冲窗口等参数，
	- glutInitWindowPosition() 定义窗口的位置，相对于屏幕左上角x, y的坐标
	- glutCreateWindow() 定义窗口的名字
- 三个回调函数
	- glutDisplayFunc() 用于更新时，执行回调函数，专注于试图的刷新
	- glutIdleFunc() 用于处理当前时间循环空闲时的回调函数，空闲时专注于星球位置的更新
	- glutKeyboardFunc() 用于处理键盘事件

通过这些参数，就可以在窗口中显示一些图像了。
## star
主要定义了星星的参数和方法，包括：
- 基本参数：自转和公转位置，星体材质，运动半径，所围绕的星球。
- 方法：
	- update：更新自转角度和公转角度。
	- show：显示星体，主要根据自转和公转信息显示星球的位置和状态，通过材质显示星球的形状和颜色。
		- glEnable：启用或禁用openGL中的某些功能，
		- glPushMatrix和glPopMatrix方法，放入或弹出当前矩阵堆栈。就是将当前矩阵作为一个副本保存或使用。
补充：这里的矩阵就涉及到OpenGL的物体建模方法了，大概意思就是先在坐标系远点描绘物体，再通过矩阵变换，将物体变换到目标位置处。这里有一个解释openGL中矩阵的作用的博客：https://blog.csdn.net/xyh930929/article/details/83715368，感觉还满详细的。
		- glRotated 矩阵变换，旋转：绕某一向量旋转，注意最后的d和f表示的时double和float
		- glTranslatef矩阵变换，平移：平移一个向量的长度
		- glBegin和glEnd绘制图形：在中间使用glVertex2f方法进行画点，根据图形的定义不同，这些点也会组成不同的图像。关于glVertex2f，这里有个博客写的很清楚：https://blog.csdn.net/qq844352155/article/details/28465919。
		- glutSolidSphere绘制球体
	- 在派生类中实现了不同星体的画法，通过glMaterialfv方法提前对材质进行一些处理

## solarSystem
主要定义摄像机的位置来绘出的图像
基本参数：描述摄像机的9个参数，相机坐标，相机所拍目标的坐标，相机视角，
在构造函数中构造相机参数和 包含星体对象的数组，每次更新和展示都直接调用star中的方法即可。
- 构造函数：通过gluLookAt方法描述相机的位置。
- onDisplay：相机拍摄，针对viewport缓冲区进行一些操作
	- glClear清空缓冲区
	- glClearColor设置颜色缓存，只起到一个set的作用，没有clear的作用
	- glMatrixMode声明一下接下来要做的操作，通过传入投影，透视，纹理三个参数来表明
	- glLoadIdentity坐标系初始化
	- gluPerspective，定义相机的镜头参数，包括视角，距离等信息。

通过相机拍摄图像，然后更新到窗口中，这就是一个简单的openGL项目流程。

代码仓库：https://github.com/1074224619/OpenGL_demo
