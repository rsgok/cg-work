// This assignment may cost you some efferts, so I give you some important HINTS, hope that may help you.
// Enjoy the coding and thinking, do pay more attention to the library functions used in OPENGL, such as how they are used? what are the parameters used? and why?

#include <stdlib.h>
#include <gl/glut.h>


float fTranslate;
float fRotate    = 0.0f;
float fScale     = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false; //是否为透视投影
bool bAnim = false; // 茶壶和桌子是否旋转
bool bWire = false; // 绘制模式是否为线形

int wHeight = 0;
int wWidth = 0;

//todo
//hint: some additional parameters may needed here when you operate the teapot
bool bTeapotRotate = false; //茶壶是否旋转
float tRotate = 0.0f; //茶壶旋转因子

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void Draw_Scene(float teapotP[])
{
	glPushMatrix();
	glTranslatef(teapotP[0], teapotP[1], teapotP[2]);
	glRotatef(90, 1, 0, 0); //notice the rotation here, you may have a TRY removing this line to see what it looks like.
	//todo; hint: when operate the teapot, you may need to change some parameters
	glRotatef(tRotate, 0, 1, 0);//控制旋转
	glutSolidTeapot(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 3.5);
	glScalef(5, 4, 1);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, 1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.5, -1, 1.5);
	Draw_Leg();
	glPopMatrix();

}

void updateView(int width, int height)
{
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width/(GLfloat)height;

	if (bPersp){
		//todo when 'p' operation, hint: use FUNCTION gluPerspective
		gluPerspective(45, whRatio, 1, 100);
	}
	else
		glOrtho(-3 ,3, -3, 3,-100,100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};
//todo; hint: you may need another ARRAY when you operate the teapot
float teapotP[] = { 0, 0, 5 };

void key(unsigned char k, int x, int y)
{
	switch(k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': {bPersp = !bPersp; updateView(wHeight, wWidth);break; }

	case ' ': {bAnim = !bAnim; break;}
	case 'o': {bWire = !bWire; break;}

	case 'a': {//todo, hint: eye[] and center[] are the keys to solve the problems
		center[0] += 0.1f;
		eye[0] += 0.1f;
		break;
			  }
	case 'd': {//todo
		center[0] -= 0.1f;
		eye[0] -= 0.1f;
		break;
			  }
	case 'w': {//todo
		center[1] -= 0.1f;
		eye[1] -= 0.1f;
		break;
			  }
	case 's': {//todo
		center[1] += 0.1f;
		eye[1] += 0.1f;
		break;
			  }
	case 'z': {//todo
		center[2] -= 0.1f;
		eye[2] -= 0.1f;
		break;
			  }
	case 'c': {//todo
		center[2] += 0.1f;
		eye[2] += 0.1f;
		break;
			  }
	//向右移动
	case 'l': {//todo, hint:use the ARRAY that you defined, and notice the teapot can NOT be moved out the range of the table.
		teapotP[0] -= 0.1f;
		if (teapotP[0] < -1.5f)
		{
			teapotP[0] = -1.5f;
		}
		break;
			  }
	//向左移动
	case 'j': {//todo
		teapotP[0] += 0.1f;
		if (teapotP[0] > 1.5f)
		{
			teapotP[0] = 1.5f;
		}
		break;
			  }
	//向前移动
	case 'i': {//todo
		teapotP[1] += 0.1f;
		if (teapotP[1] > 1.5f)
		{
			teapotP[1] = 1.5f;
		}
		break;
			  }
	//向后移动
	case 'k': {//todo
		teapotP[1] -= 0.1f;
		if (teapotP[1] < -1.5f)
		{
			teapotP[1] = -1.5f;
		}		
		break;
			  }
	case 'e': {//控制茶壶是否旋转
		bTeapotRotate = !bTeapotRotate;
		break;
			  }
	}
}


void redraw()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2], //  观察位置
		center[0], center[1], center[2], //	物体位置
		0, 1, 0);				//	观察方向(0, 1, 0) 

	if (bWire) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = {5,5,5,1};

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
	glEnable(GL_LIGHT0);

	//	glTranslatef(0.0f, 0.0f,-6.0f);			// Place the triangle at Center
	glRotatef(fRotate, 0, 1.0f, 0);			// Rotate around Y axis
	glRotatef(-90, 1, 0, 0);
	glScalef(0.2, 0.2, 0.2);
	Draw_Scene(teapotP);						// Draw Scene

	if (bAnim) fRotate    += 0.5f;
	if (bTeapotRotate) tRotate += 0.5f; //茶壶旋转

	//todo; hint: when you want to rotate the teapot, you may like to add another line here =)
	glutSwapBuffers();
}

int main (int argc,  char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(480,480);
	int windowHandle = glutCreateWindow("Ex 3");

	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}


