#include"GL/glut.h"
#include"solarsystem.h"

#define REST 700
#define REST_Y (-REST)
#define REST_Z (REST)
// 公转半径
#define SUN_RADIUS 48.74
#define MER_RADIUS  7.32
#define VEN_RADIUS 18.15
#define EAR_RADIUS 19.13
#define MOO_RADIUS  6.15
#define MAR_RADIUS 10.19
#define JUP_RADIUS 42.90
#define SAT_RADIUS 36.16
#define URA_RADIUS 25.56
#define NEP_RADIUS 24.78

// 距太阳的距离
#define MER_DIS   62.06
#define VEN_DIS  115.56
#define EAR_DIS  168.00
#define MOO_DIS   26.01
#define MAR_DIS  228.00
#define JUP_DIS  333.40
#define SAT_DIS  428.10
#define URA_DIS 848.00
#define NEP_DIS 949.10

// 运动速度
#define MER_SPEED   87.0
#define VEN_SPEED  225.0
#define EAR_SPEED  365.0
#define MOO_SPEED   30.0
#define MAR_SPEED  687.0
#define JUP_SPEED 1298.4
#define SAT_SPEED 3225.6
#define URA_SPEED 3066.4
#define NEP_SPEED 6014.8

// 自转速度
#define SELFROTATE 3

// 为了方便操作数组，定义一个设置多为数组的宏
#define SET_VALUE_3(name, value0, value1, value2) \
                   ((name)[0])=(value0), ((name)[1])=(value1), ((name)[2])=(value2)


SolarSystem::SolarSystem() {
	// 设置视角的参数
	m_viewX = 0;
	m_viewY = REST_Y;
	m_viewZ = REST_Z;
	m_centerX = m_centerY = m_centerZ = 0;
	m_upX = m_upY = 0;
	m_upZ = 1;

	gluLookAt(m_viewX, m_viewY, m_viewZ, m_centerX, m_centerY, m_centerZ, m_upX, m_upY, m_upZ);
	
	// 太阳
	GLfloat rgbColor[3] = { 1, 0, 0 };
	m_stars[Sun] = new LightPlanet(SUN_RADIUS, 0, 0, SELFROTATE, 0, rgbColor);
	// 水星
	SET_VALUE_3(rgbColor, .2, .2, .5);
	m_stars[Mercury] = new Planet(MER_RADIUS, MER_DIS, MER_SPEED, SELFROTATE, m_stars[Sun], rgbColor);
	// 金星
	SET_VALUE_3(rgbColor, 1, .7, 0);
	m_stars[Venus] = new Planet(VEN_RADIUS, VEN_DIS, VEN_SPEED, SELFROTATE, m_stars[Sun], rgbColor);
	// 地球
	SET_VALUE_3(rgbColor, 0, 1, 0);
	m_stars[Earth] = new Planet(EAR_RADIUS, EAR_DIS, EAR_SPEED, SELFROTATE, m_stars[Sun], rgbColor);
	// 月亮
	SET_VALUE_3(rgbColor, 1, 1, 0);
	m_stars[Moon] = new Planet(MOO_RADIUS, MOO_DIS, MOO_SPEED, SELFROTATE, m_stars[Earth], rgbColor);
	// 火星
	SET_VALUE_3(rgbColor, 1, .5, .5);
	m_stars[Mars] = new Planet(MAR_RADIUS, MAR_DIS, MAR_SPEED, SELFROTATE, m_stars[Sun], rgbColor);
	// 木星
	SET_VALUE_3(rgbColor, 1, 1, .5);
	m_stars[Jupiter] = new Planet(JUP_RADIUS, JUP_DIS, JUP_SPEED, SELFROTATE, m_stars[Sun], rgbColor);
	// 土星
	SET_VALUE_3(rgbColor, .5, 1, .5);
	m_stars[Saturn] = new Planet(SAT_RADIUS, SAT_DIS, SAT_SPEED, SELFROTATE, m_stars[Sun], rgbColor);
	// 天王星
	SET_VALUE_3(rgbColor, .4, .4, .4);
	m_stars[Uranus] = new Planet(URA_RADIUS, URA_DIS, URA_SPEED, SELFROTATE, m_stars[Sun], rgbColor);
	// 海王星
	SET_VALUE_3(rgbColor, .5, .5, 1);
	m_stars[Neptune] = new Planet(NEP_RADIUS, NEP_DIS, NEP_SPEED, SELFROTATE, m_stars[Sun], rgbColor);
}
SolarSystem::~SolarSystem() {
	for (int i = 0; i < STARS_NUM; ++i) {
		delete m_stars[i];
	}
}

void SolarSystem::onDisplay() {
	// 清除 viewport 缓冲区
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 清空并设置颜色缓存
	glClearColor(0.7, 0.7, 0.7, 0.1);
	// 指定投影矩阵
	glMatrixMode(GL_PROJECTION);
	// 将指定的矩阵指定为单位矩阵
	glLoadIdentity();
	// 指定当前的观察视景体
	gluPerspective(75.0f, 1.0f, 1.0f, 40000000);

	// 指定当前矩阵为视景矩阵堆栈应用术后的矩阵操作
	glMatrixMode(GL_MODELVIEW);
	// 指定当前的矩阵为单位矩阵
	glLoadIdentity();
	// 定义视图矩阵，并与当前矩阵相乘
	gluLookAt(m_viewX, m_viewY, m_viewZ, m_centerX, m_centerY, m_centerZ, m_upX, m_upY, m_upZ);
	
	// 设置第一个光源(0号光源)
	glEnable(GL_LIGHT0);
	// 启用光源
	glEnable(GL_LIGHTING);
	// 启用深度测试，根据坐标的远近自动隐藏被遮住的图形
	glEnable(GL_DEPTH_TEST);

	// 绘制星球
	for (int i = 0; i < STARS_NUM; i++)
		m_stars[i]->draw();

	// 我们在 main 函数中初始化显示模式时使用了 GLUT_DOUBLE
	// 需要使用 glutSwapBuffers 在绘制结束后实现双缓冲的缓冲区交换
	glutSwapBuffers();
}
void SolarSystem::onUpdate() {
	for (int i = 0; i < STARS_NUM; ++i) {
		m_stars[i]->update(TIMEPAST);
	}onDisplay(); // 刷新显示
}

#define OFFSET 20
void SolarSystem::onKeyboard(unsigned char key, int x, int y) {
	if (key == 'w') m_viewY += OFFSET;
	else if (key == 's') m_viewZ += OFFSET;
	else if (key == 'S') m_viewZ -= OFFSET;
	else if (key == 'a') m_viewX -= OFFSET;
	else if (key == 'd') m_viewX += OFFSET;
	else if (key == 'x') m_viewY -= OFFSET;
	else if (key == 'r') {
		m_viewX = 0; m_viewY = REST_Y; m_viewZ = REST_Z;
		m_centerX = m_centerY = m_centerZ = 0;
		m_upX = m_upY = 0;  m_upZ = 1;
	}
	else if (key == 27) exit(0);
}