#include<cmath>
#include<cstdlib>
#include"gl/glut.h"
#include"solarsystem.h"

#define WINDOW_X_POS 50
#define WINDOW_Y_POS 50
#define WIDTH 700
#define HEIGHT 700

SolarSystem solarsystem;

void onDisplay() {
	solarsystem.onDisplay();
}
void onUpdate() {
	solarsystem.onUpdate();
}
void onKeyboard(unsigned char key, int x, int y) {
	solarsystem.onKeyboard(key, x, y);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowPosition(WINDOW_X_POS, WINDOW_Y_POS);
	glutCreateWindow("SolarSystem");

	glutDisplayFunc(onDisplay); // 需要更新时执行回调函数
	glutIdleFunc(onUpdate); // 处理当前时间循环空闲时的回调
	glutKeyboardFunc(onKeyboard); // 处理键盘事件

	glutMainLoop();
	return 0;
}