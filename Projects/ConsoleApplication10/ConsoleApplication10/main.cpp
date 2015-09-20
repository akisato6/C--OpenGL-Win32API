#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#pragma comment(lib,"glew32.lib")
#include <Gl/glew.h>
#include <GL/freeglut.h>
#include "Header.h"

#define WIDTH 320
#define HEIGHT 240

float angle = 0.0f;
MODEL* model;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, WIDTH / HEIGHT, 0.1, 2000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 1500.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glRotatef(angle, 1.0f, 0.0f, 0.0f);//âÒì]
	glRotatef(angle, 0.0f, 1.0f, 0.0f);//âÒì]

	model->Draw();
	glutSwapBuffers();
}
void idle(void)
{
	angle += 2.0f;
	Sleep(1);
	glutPostRedisplay();
}
void Init(){
	glewInit();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	model = new MODEL("box.obj");
}
int main(int argc, char *argv[])
{
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("OBJÉçÅ[É_");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	Init();
	glutMainLoop();
	return 0;
}