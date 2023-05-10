#pragma once
#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include"star.h"

#define TIMEPAST 1
#define SELFROTATE 3
#define STARS_NUM 10

enum STARS {
	//日，水，金，地球，月，火，木，土，天王，海王
	Sun, Mercury, Venus, Earth, Moon, Mars, Jupiter, Saturn, Uranus, Neptune
};

class SolarSystem {
private:
	Star* m_stars[STARS_NUM];
	// 观察视角参数
	GLdouble m_viewX, m_viewY, m_viewZ;
	GLdouble m_centerX, m_centerY, m_centerZ;
	GLdouble m_upX, m_upY, m_upZ;
public:
	SolarSystem();
	~SolarSystem();

	void onDisplay();
	void onUpdate();
	void onKeyboard(unsigned char key, int x, int y);
};

#endif // !SOLARSYSTEM_H
