#include<cmath>
#include"GL/glut.h"
#include"star.h"

#define PI acos(-1)
#define max(a, b) (a)>(b)?(a):(b)

Star::Star(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parentStar) {
	m_radius = radius;
	m_distance = distance;
	m_speed = max(0.0, 360.0 / speed); // 线速度转为角速度
	m_selfSpeed = selfSpeed;
	m_parentStar = parentStar;
	for (int i = 0; i < 4; ++i) {
		m_rgbaColor[i] = 1.0;
	}
	m_alpha = m_alphaSelf = 0;
}
void Star::drawStar() {
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);

	int n = 1440;
	// 保存 openGL 当前矩阵环境
	glPushMatrix();
	{
		// 公转行星，先转到公转行星的轨道上
		if (m_parentStar != 0 && m_parentStar->m_distance > 0) {
			// 图形沿z轴旋转alpha
			glRotated(m_parentStar->m_alpha, 0, 0, 1);
			// x轴方向平移dis, 其余y, z不变
			glTranslatef(m_parentStar->m_distance, 0.0, 0.0);
		}
		//绘制轨道
		glBegin(GL_LINES);
		for (int i = 0; i < n; ++i) {
			glVertex2f(m_distance * std::cos(2 * PI * i / n),
				m_distance * std::sin(2 * PI * i / n));
		}glEnd();

		// 绕原点公转
		glRotatef(m_alpha, 0, 0, 1);
		glTranslatef(m_distance, 0.0, 0.0);

		// 自转
		glRotatef(m_alphaSelf, 0, 0, 1);
		//绘制颜色
		glColor3f(m_rgbaColor[0], m_rgbaColor[1], m_rgbaColor[2]);
		glutSolidSphere(m_radius, 40, 32); // 绘制球体
	}
	glPopMatrix();
}
void Star::update(long timeSpan) {
	m_alpha += timeSpan * m_speed; // 更新公转角度
	m_alphaSelf += m_selfSpeed; // 更新自传角度
}

Planet::Planet(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parentStar, GLfloat rgbColor[3]):
Star(radius, distance, speed, selfSpeed, parentStar){
	for (int i = 0; i < 3; ++i)
		m_rgbaColor[i] = rgbColor[i];
	m_rgbaColor[3] = 1.0;
}
void Planet::drawPlanet() {
	// 不发光的星球绘制光照效果
	GLfloat mat_ambient[] = { 0.0, 0.0, 0.5, 1.0 };
	GLfloat mat_diffuse[] = { 0.0, 0.0, 0.5, 1.0 };
	GLfloat mat_specular[] = { 0.0, 0.0, 0.5, 1.0 };
	GLfloat mat_emission[] = { m_rgbaColor[0], m_rgbaColor[1], m_rgbaColor[2], m_rgbaColor[3] };
	GLfloat mat_shininess = 90.0f;

	// 指定照明模型的材料参数(
	// 材质属性用于物体的那一面, 材质属性, 设置属性值)
	// 从上到下, 分别为 环境颜色, 散射颜色, 镜面反射颜色, 镜面反射指数, 发射光颜色, 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);//非向量版本
}

LightPlanet::LightPlanet(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parentStar, GLfloat rgbColor[3]):
Planet(radius, distance, speed, selfSpeed, parentStar, rgbColor) {
	;
}
void LightPlanet::drawLight() {
	// 发光的星球绘制光照效果
	GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position); // 指定零号光源的位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);  // 表示各种光线照射到该材质上，经过很多次反射后追踪遗留在环境中的光线强度
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);  // 漫反射后的光照强度
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular); // 镜面反射后的光照强度
}