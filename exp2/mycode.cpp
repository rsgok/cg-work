
#include "glut.h"

float fTranslate;
float fRotate;
float fScale = 1.0;

typedef struct GLPositon2f
{
	GLfloat x;
	GLfloat y;
} Point;

void Draw_Desk_board()
{
    glBegin(GL_LINE_LOOP);
        glVertex3f(-1.0f, -0.8f, 0.0f);
        glVertex3f(-1.0f, 0.8f, 0.0f);
        glVertex3f(1.0f, 0.8f, 0.0f);
        glVertex3f(1.0f, -0.8f, 0.0f);
	glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(-1.0f, -0.8f, -0.2f);
        glVertex3f(-1.0f, 0.8f, -0.2f);
        glVertex3f(1.0f, 0.8f, -0.2f);
        glVertex3f(1.0f, -0.8f, -0.2f);
	glEnd();
    glBegin(GL_LINES);
        glVertex3f(-1.0f, -0.8f, 0.0f);
        glVertex3f(-1.0f, -0.8f, -0.2f);
	glEnd();
    glBegin(GL_LINES);
        glVertex3f(-1.0f, 0.8f, 0.0f);
        glVertex3f(-1.0f, 0.8f, -0.2f);
	glEnd();
    glBegin(GL_LINES);
        glVertex3f(1.0f, 0.8f, 0.0f);
        glVertex3f(1.0f, 0.8f, -0.2f);
	glEnd();
    glBegin(GL_LINES);
        glVertex3f(1.0f, -0.8f, 0.0f);
        glVertex3f(1.0f, -0.8f, -0.2f);
	glEnd();
}
void Draw_Desk_leg(Point legTopCenterPoint)
{
    Point leftdown;
    Point rightdown;
    Point leftup;
    Point rightup;
    leftdown.x = legTopCenterPoint.x - 0.1;
    leftdown.y = legTopCenterPoint.y - 0.1;
    rightdown.x = legTopCenterPoint.x + 0.1;
    rightdown.y = legTopCenterPoint.y - 0.1;
    leftup.x = legTopCenterPoint.x - 0.1;
    leftup.y = legTopCenterPoint.y + 0.1;
    rightup.x = legTopCenterPoint.x + 0.1;
    rightup.y = legTopCenterPoint.y + 0.1;
    glBegin(GL_LINE_LOOP);
        glVertex3f(leftdown.x, leftdown.y, -0.2f);
        glVertex3f(leftup.x, leftup.y, -0.2f);
        glVertex3f(rightup.x, rightup.y, -0.2f);
        glVertex3f(rightdown.x, rightdown.y, -0.2f);
	glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex3f(leftdown.x, leftdown.y, -0.8f);
        glVertex3f(leftup.x, leftup.y, -0.8f);
        glVertex3f(rightup.x, rightup.y, -0.8f);
        glVertex3f(rightdown.x, rightdown.y, -0.8f);
	glEnd();
    glBegin(GL_LINES);
        glVertex3f(leftdown.x, leftdown.y, -0.2f);
        glVertex3f(leftdown.x, leftdown.y, -0.8f);
	glEnd();
    glBegin(GL_LINES);
        glVertex3f(leftup.x, leftup.y, -0.2f);
        glVertex3f(leftup.x, leftup.y, -0.8f);
	glEnd();
    glBegin(GL_LINES);
        glVertex3f(rightup.x, rightup.y, -0.2f);
        glVertex3f(rightup.x, rightup.y, -0.8f);
	glEnd();
    glBegin(GL_LINES);
        glVertex3f(rightdown.x, rightdown.y, -0.2f);
        glVertex3f(rightdown.x, rightdown.y, -0.8f);
	glEnd();
}
void Draw_Desk()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    // draw desk top face
	Draw_Desk_board();
    // draw desk legs
    Point legTopCenterPoint;
    legTopCenterPoint.x = -0.8;
    legTopCenterPoint.y = 0.6;
    Draw_Desk_leg(legTopCenterPoint);
    legTopCenterPoint.x = 0.8;
    legTopCenterPoint.y = 0.6;
    Draw_Desk_leg(legTopCenterPoint);
    legTopCenterPoint.x = -0.8;
    legTopCenterPoint.y = -0.6;
    Draw_Desk_leg(legTopCenterPoint);
    legTopCenterPoint.x = 0.8;
    legTopCenterPoint.y = -0.6;
    Draw_Desk_leg(legTopCenterPoint);
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void idle()
{
	glutPostRedisplay();
}

void redraw()
{
  glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	
	glPushMatrix();
		glTranslatef(-3.0f, 0.0f,-6.0f);		// Place the desk Left
		glTranslatef(0.0f, fTranslate, 0.0f);	// Translate in Y direction
		Draw_Desk();						// Draw desk					
	glPopMatrix();

    glPushMatrix();
		glTranslatef(0.0f, 0.0f,-6.0f);			// Place the desk at Center
		glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
		Draw_Desk();						// Draw desk
	glPopMatrix();

    glPushMatrix();
		glTranslatef(3.0f, 0.0f,-6.0f);		// Place the desk right
		glScalef(fScale, fScale, fScale);     // scale
		Draw_Desk();						// Draw desk					
	glPopMatrix();

	fTranslate += 0.001f;
	fRotate    += 0.5f;
    fScale -= 0.001f;

	if(fTranslate > 0.5f) fTranslate = 0.0f;
    if(fScale < -0.001f) fScale = 1.0f;
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(1000,500);                                                  
	glutCreateWindow("Exercise2");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);		
	glutIdleFunc(idle);					

	glutMainLoop();

	return 0;
}


