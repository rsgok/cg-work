#include "gl/glut.h"
#include "math.h"

const GLfloat PI = 3.14;

typedef struct GLPositon2f
{
	GLfloat x;
	GLfloat y;
} Point;

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
void starPart(GLfloat centerX, GLfloat centerY, GLfloat endX, GLfloat endY) {
	float cf1 = tan(PI / 10) / (tan(PI / 5) + tan(PI / 10));
	float cf2 = tan(PI / 5);

	Point PQ = { endX - centerX, endY - centerY };
	Point PH = { cf1 * PQ.x, cf1 * PQ.y };
	Point HM = { cf2 * PH.y, cf2 * (-PH.x) };

	Point M = { centerX + PH.x + HM.x, centerY + PH.y + HM.y };
	Point N = { centerX + PH.x - HM.x, centerY + PH.y - HM.y };

	glBegin(GL_POLYGON);
		glVertex2f(centerX, centerY);
		glVertex2f(M.x, M.y);
		glVertex2f(endX, endY);
		glVertex2f(N.x, N.y);
	glEnd();
}
void rotate(GLfloat centerX, GLfloat centerY, GLfloat* endX, GLfloat* endY, float rad) {
	Point vector = { *endX - centerX, *endY - centerY };
	Point resultV = {
		cos(rad) * vector.x + sin(rad) * vector.y,
		cos(rad) * vector.y + sin(rad) * (-vector.x)
	};

	*endX = centerX + resultV.x;
	*endY = centerY + resultV.y;
}
void singleStar(GLfloat centerX, GLfloat centerY, GLfloat endX, GLfloat endY) {
	for (int i = 0; i < 5; i++)
	{
		starPart(centerX, centerY, endX, endY);
		rotate(centerX, centerY, &endX, &endY, 2 * PI / 5);
	}
}
void star()
{
	glColor3f(1, 1, 0);

	singleStar(-0.60, 0.30, -0.78, 0.36);

	singleStar(-0.30, 0.48, -0.24, 0.48);
	singleStar(-0.18, 0.36, -0.24, 0.36);
	singleStar(-0.18, 0.18, -0.18, 0.24);
	singleStar(-0.30, 0.06, -0.24, 0.06);
}
void display()
{
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
	glutInitWindowSize(800, 800);
	glutCreateWindow("The Nation Flag of China");

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}