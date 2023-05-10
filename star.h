#ifndef STAR_H
#define STAR_H

#pragma once
#include"GL/glut.h"

class Star {
protected:
	GLfloat m_alphaSelf, m_alpha;// 自转和公转信息
public:
	GLfloat m_radius; // 星球半径
	GLfloat m_speed, m_selfSpeed; // 公转和自转速度
	GLfloat m_distance; // 距离公转距离
	GLfloat m_rgbaColor[4]; // 星球颜色

	Star* m_parentStar; // 父节点星球
	// 构造函数 需要旋转半径，自转和公转速度， 父节点星球
	//Star() {}
	Star(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parentStar);
	// 绘画移动旋转等活动
	void drawStar();
	// 向子类开放重写功能
	virtual void draw() { drawStar(); };
	// 更新的时间跨度
	virtual void update(long timeSpan);
};

class Planet : public Star {
public:
	//Planet() {}
	Planet(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parentStar, GLfloat rgbColor[3]);

	void drawPlanet();
	// 向子类开放重写功能
	virtual void drwa() { drawPlanet(); drawStar(); }
};

class LightPlanet :public Planet {
public:
	LightPlanet(GLfloat radius, GLfloat distance, GLfloat speed, GLfloat selfSpeed, Star* parentStar, GLfloat rgbColor[3]);
	void drawLight();
	virtual void draw() { drawLight(); drawPlanet(); drawStar(); }
};

#endif