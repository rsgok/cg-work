#include "gl/glut.h"
#include "math.h"
#include <iostream>

using namespace std;

const GLfloat PI = 3.14;

const int WIDTH = 500;
const int HEIGHT = 500;
const float ASPECT = float(WIDTH) / HEIGHT;

typedef struct GLPositon2f
{
	GLfloat x;
	GLfloat y;
} Point;

void windowResizeHandler(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int w = height * ASPECT;           // w is width adjusted for aspect ratio
	int left = (width - w) / 2;
	glViewport(left, 0, w, height);       // fix up the viewport to maintain aspect ratio
	gluOrtho2D(0, WIDTH, HEIGHT, 0);   // only the window is changing, not the camera
	glMatrixMode(GL_MODELVIEW);

	glutPostRedisplay();
}

void rect()
{
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2f(-0.9, 0.6);
	glVertex2f(0.9, 0.6);
	glVertex2f(0.9, -0.6);
	glVertex2f(-0.9, -0.6);
	glEnd();
}
void starPart(Point centerPoint, GLfloat R, int angle) {

	Point topPoint, leftPoint, rightPoint;
	GLfloat tLine, tx, ty;

	tLine = R * sin(PI / 10) / sin(7 * PI / 10);
	tx = tLine * sin(PI / 5);
	ty = tLine * sin(3 * PI / 10);
	// origin
	topPoint.x = centerPoint.x;
	topPoint.y = centerPoint.y + R;
	leftPoint.y = rightPoint.y = centerPoint.y + ty;
	leftPoint.x = centerPoint.x - tx;
	rightPoint.x = centerPoint.x + tx;

	glPushMatrix();
	glTranslatef(centerPoint.x, centerPoint.y, 0);
	glRotatef(angle, 0, 0, 1);
	glTranslatef(-centerPoint.x, -centerPoint.y, 0);
	// draw
	glBegin(GL_POLYGON);
	glVertex2f(centerPoint.x, centerPoint.y);
	glVertex2f(leftPoint.x, leftPoint.y);
	glVertex2f(topPoint.x, topPoint.y);
	glVertex2f(rightPoint.x, rightPoint.y);
	glEnd();
	glPopMatrix();
	//测试分支独立性
}
void singleStar(Point centerPoint, GLfloat R, int clockwiseAngle) {
	cout << "single Star" << endl;
	for (int i = 0; i < 5; i++) starPart(centerPoint, R, i * 72 - clockwiseAngle);
}
void star()
{
	//cout << "star" << endl;
	glColor3f(1, 1, 0);
	// big star
	singleStar({ -0.6, 0.3 }, 0.18, 0);
	// four small stars
	singleStar({ -0.3, 0.48 }, 0.06, 18);
	singleStar({ -0.18, 0.18 }, 0.06, -18);
	singleStar({ -0.18, 0.36 }, 0.06, 0);
	singleStar({ -0.3, 0.06 }, 0.06, 18);
}

//void myInit()
//{
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glViewport(0, 0, InitWindowSize[0], InitWindowSize[1]);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(-15.0, 15.0, -15.0, 15.0);
//	glMatrixMode(GL_MODELVIEW);
//}
void display()
{
	//cout << "display" << endl;
	glClear(GL_COLOR_BUFFER_BIT);

	rect();
	star();

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WIDTH, HEIGHT);
	glLoadIdentity();
	glutCreateWindow("The Nation Flag of China");
	glutDisplayFunc(display);
	//注册窗口大小改变时回调函数
	//glutReshapeFunc(windowResizeHandler);
	//myInit();
	glutMainLoop();

	return 0;
}