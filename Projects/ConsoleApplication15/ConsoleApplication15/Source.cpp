#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <GL/freeglut.h>
#include <math.h>

#define WIDTH 600
#define HEIGHT 440
#define PAI 3.1415



#pragma warning (disable : 4996) 

int wheel;
int Mouse_X, Mouse_Y, Mouse_judge;
char str[256];
void *font = GLUT_BITMAP_HELVETICA_18;


GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
GLfloat blue[] = { 0.2, 0.2, 1, 1.0 };
GLfloat orange[] = { 1.0f, 0.6f, 0.0f, 1.0f };
GLfloat black[] = { 0, 0, 0, 0 };

GLfloat light0pos[] = { 10, 10, -30, 1.0 };
GLfloat light1pos[] = { -10, 10, -30, 1 };
GLfloat light2pos[] = { 10, -10, -30, 1 };
GLfloat light3pos[] = { 10, 10, -30, 1.0 };
GLfloat light4pos[] = { -10, -10, -30, 1 };
GLfloat light5pos[] = { -10, 10, -30, 1 };
int time=0;
int timecheck = 0;


void printmath(float x, float y, float z, int math)
{
	char str[256];
	sprintf(str, "%d", math); /* 文字(char)配列strにaを数字(%d)に変換した文字列を格納 */
	glRasterPos3d(x, y, z);
	for (int i = 0; i < strlen(str); i++) { /* 文字列の長さ繰り返す */
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]); /* 1文字ずつ */
	}

}

void points(float x, float y, float z)
{
	glColor3f(0, 1.0, 1.0);
	float pointsize = 0.1;
	glPointSize(pointsize);

	glBegin(GL_POINTS);
	glVertex3f(x, y, z);
	glEnd();
}
void line(float x1, float y1, float z1, float x2, float y2, float z2)
{



	glBegin(GL_LINES);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);
	glEnd();
}

void seihoukei(float x, float y,float z)
{
	float pointsize = 9;
	glPointSize(pointsize);
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(x, 0, 0);
	glVertex3d(x, 0, z);
	glVertex3d(0, 0, z);
	
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, z);
	glVertex3d(0, y, z);
	glVertex3d(0, y, 0);
	glEnd();
	
	
	glBegin(GL_POLYGON);
	glVertex3d(0, y, 0);
	glVertex3d(0, y, z);
	glVertex3d(x, y, z);
	glVertex3d(x, y, 0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3d(x, 0, 0);
	glVertex3d(x, 0, z);
	glVertex3d(x, y, z);
	glVertex3d(x, y, 0);
	glEnd();
	
	
	/*glBegin(GL_POLYGON);
	glVertex3d(0, 0, z);
	glVertex3d(x, 0, z);
	glVertex3d(x, y, z);
	glVertex3d(0, y, z);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3d(0, 0, 0);
	glVertex3d(x, 0, 0);
	glVertex3d(x, y, 0);
	glVertex3d(0, y, 0);
	glEnd();
	*/
}
void sikaku(float x, float y, float z)
{
	float pointsize = 9;
	glPointSize(pointsize);
	glBegin(GL_LINE_LOOP);
	glVertex3d(0, 0, 0);
	glVertex3d(x, 0, 0);
	glVertex3d(x, 0, z);
	glVertex3d(0, 0, z);

	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, z);
	glVertex3d(0, y, z);
	glVertex3d(0, y, 0);
	glEnd();


	glBegin(GL_LINE_LOOP);
	glVertex3d(0, y, 0);
	glVertex3d(0, y, z);
	glVertex3d(x, y, z);
	glVertex3d(x, y, 0);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3d(x, 0, 0);
	glVertex3d(x, 0, z);
	glVertex3d(x, y, z);
	glVertex3d(x, y, 0);
	glEnd();


	glBegin(GL_LINE_LOOP);
	glVertex3d(0, 0, z);
	glVertex3d(x, 0, z);
	glVertex3d(x, y, z);
	glVertex3d(0, y, z);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3d(0, 0, 0);
	glVertex3d(x, 0, 0);
	glVertex3d(x, y, 0);
	glVertex3d(0, y, 0);
	glEnd();
	
}
void tyouhoukei1(float x, float y, float z)
{

	int i = 0;
	GLdouble vertex1[][3] = {
		{ -x / 2, -y / 2, -z / 2 }, /* A */
		{ x / 2, -y / 2, -z / 2 }, /* B */
		{ x / 2, y / 2, -z / 2 }, /* C */
		{ -x / 2, y / 2, -z / 2 }, /* D */
		{ -x / 2, -y / 2, z / 2 }, /* E */
		{ x / 2, -y / 2, z / 2 }, /* F */
		{ x / 2, y / 2, z / 2 }, /* G */
		{ -x / 2, y / 2, z / 2 }  /* H */
	};
	int edge[][2] = {
		{ 0, 1 }, /* ア (A-B) */
		{ 1, 2 }, /* イ (B-C) */
		{ 2, 3 }, /* ウ (C-D) */
		{ 3, 0 }, /* エ (D-A) */
		{ 4, 5 }, /* オ (E-F) */
		{ 5, 6 }, /* カ (F-G) */
		{ 6, 7 }, /* キ (G-H) */
		{ 7, 4 }, /* ク (H-E) */
		{ 0, 4 }, /* ケ (A-E) */
		{ 1, 5 }, /* コ (B-F) */
		{ 2, 6 }, /* サ (C-G) */
		{ 3, 7 }  /* シ (D-H) */
	};

	glBegin(GL_POLYGON);
	for (i = 0; i < 12; ++i) {
		glVertex3dv(vertex1[edge[i][0]]);
		glVertex3dv(vertex1[edge[i][1]]);
	}
	glEnd();

}

void tyouhoukei2()
{

	int i = 0;
	GLdouble vertex2[][3] = {
		{ 0, 0, -6.3 }, /* A */
		{ 6, -3, -6.3 }, /* B */
		{ 6, 0, -6.3 }, /* C */
		{ -6, 0, -6.3 }, /* D */
		{ -6, -3, -5.7 }, /* E */
		{ 6, -3, -5.7 }, /* F */
		{ 6, 0, -5.7 }, /* G */
		{ -6, 0, -5.7 }  /* H */
	};
	int edge[][2] = {
		{ 0, 1 }, /* ア (A-B) */
		{ 1, 2 }, /* イ (B-C) */
		{ 2, 3 }, /* ウ (C-D) */
		{ 3, 0 }, /* エ (D-A) */
		{ 4, 5 }, /* オ (E-F) */
		{ 5, 6 }, /* カ (F-G) */
		{ 6, 7 }, /* キ (G-H) */
		{ 7, 4 }, /* ク (H-E) */
		{ 0, 4 }, /* ケ (A-E) */
		{ 1, 5 }, /* コ (B-F) */
		{ 2, 6 }, /* サ (C-G) */
		{ 3, 7 }  /* シ (D-H) */
	};

	glBegin(GL_LINE_LOOP);
	for (i = 0; i < 12; ++i) {
		glVertex3dv(vertex2[edge[i][0]]);
		glVertex3dv(vertex2[edge[i][1]]);
	}
	glEnd();

}

void tyouhoukei3()
{

	int i = 0;
	GLdouble vertex3[][3] = {
		{ -6.3, -3, -22 }, /* A */
		{ -5.7, -3, -22 }, /* B */
		{ -5.7, 0, -22 }, /* C */
		{ -6.3, 0, -22 }, /* D */
		{ -6.3, -3, -10 }, /* E */
		{ -5.7, -3, -10 }, /* F */
		{ -5.7, 0, -10 }, /* G */
		{ -6.3, 0, -10 }  /* H */
	};
	int edge[][2] = {
		{ 0, 1 }, /* ア (A-B) */
		{ 1, 2 }, /* イ (B-C) */
		{ 2, 3 }, /* ウ (C-D) */
		{ 3, 0 }, /* エ (D-A) */
		{ 4, 5 }, /* オ (E-F) */
		{ 5, 6 }, /* カ (F-G) */
		{ 6, 7 }, /* キ (G-H) */
		{ 7, 4 }, /* ク (H-E) */
		{ 0, 4 }, /* ケ (A-E) */
		{ 1, 5 }, /* コ (B-F) */
		{ 2, 6 }, /* サ (C-G) */
		{ 3, 7 }  /* シ (D-H) */
	};

	glBegin(GL_POLYGON);
	for (i = 0; i < 12; ++i) {
		glVertex3dv(vertex3[edge[i][0]]);
		glVertex3dv(vertex3[edge[i][1]]);
	}
	glEnd();

}

void circle(float x, float y, float z, float r)
{
	glPushMatrix();
	glTranslated(x, y, z);
	glutSolidSphere(r, 16, 16);
	glPopMatrix();
}


//クォータニオン構造体
struct Quaternion
{
	double w;
	double x;
	double y;
	double z;
};
//回転マトリックス
double Rotate[16];

Quaternion Target;
Quaternion current = { 1.0, 0.0, 0.0, 0.0 };

//演算子のオーバーロード Quaternionの積
Quaternion & operator *(Quaternion &q1, Quaternion &q2)
{
	Quaternion q0 = {
		q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
		q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
		q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
		q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
	};
	q1 = q0;
	return q1;
}

//クォータニオンから回転行列を算出
void qtor(double *r, Quaternion q)
{
	double xx = q.x * q.x * 2.0;
	double yy = q.y * q.y * 2.0;
	double zz = q.z * q.z * 2.0;
	double xy = q.x * q.y * 2.0;
	double yz = q.y * q.z * 2.0;
	double zx = q.z * q.x * 2.0;
	double xw = q.x * q.w * 2.0;
	double yw = q.y * q.w * 2.0;
	double zw = q.z * q.w * 2.0;
	double r1[16] = { 1.0 - yy - zz, xy + zw, zx - yw, 0.0,
		xy - zw, 1.0 - zz - xx, yz + xw, 0.0,
		zx + yw, yz - xw, 1.0 - xx - yy, 0.0,
		0.0, 0.0, 0.0, 1.0 };
	for (int i = 0; i < 16; i++) {
		r[i] = r1[i];
	}
}


typedef struct{
	float x, y, z, r;
	int b, c;
}Position;

typedef struct
{

	Position pos[10000];
	int step, particle;
	char name[10000];
	int count;
}Step;

Step step[1000];


int file_read(char *filename)
{
	FILE *fp;
	char    buf[256];
	int i = 0;
	int j = 0;
	int k = 0;
	int count = 0;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("File %s is not created\n", filename);
		return 0;
	}

	while (fgets(buf, 1000, fp) != NULL)
	{

		switch (buf[0])
		{
		case 'S':
			sscanf(buf + 6, "%d %d", &step[i].step, &step[i].particle);

			i++;
			break;

		case '0':
			sscanf(buf, "%f %f %f %f %d %d",
				&step[i].pos[j].x, &step[i].pos[j].y,
				&step[i].pos[j].z, &step[i].pos[j].r,
				&step[i].pos[j].b, &step[i].pos[j].c);
			++j;
			break;
		case'e':
			step[k].count = j;
			k++;
			count = k;
			j = 0;
			break;

		default:
			break;

		}
	}
	//printf("%d", count);
	fclose(fp);	return 0;
}


void display()
{
	int i = 0;
	int j = 0;
	if (time >= 30)
	{
		time = 30;
	}
	if (time<=0)
	{
		time = 0;
	}
	int Step = time;
	int Particle = time * 10;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, WIDTH, HEIGHT);

	
	/*文字描写*/
	glPushMatrix();
	glRasterPos3d(200, 300, -80);
	glutBitmapString(font, reinterpret_cast<const unsigned char*>("Step     :"));
	printmath(200, 700, -75, Step);
	glRasterPos3d(200, 300, -50);
	glutBitmapString(font, reinterpret_cast<const unsigned char*>("Particle :"));
	printmath(200, 700, -20, Particle);

	glRasterPos3d(200, 700, 180);
	glutBitmapString(font, reinterpret_cast<const unsigned char*>("Go  :'G'"));
	glRasterPos3d(200, 700, 280);
	glutBitmapString(font, reinterpret_cast<const unsigned char*>("Back:'B'"));
	glRasterPos3d(200, 700, 380);
	glutBitmapString(font, reinterpret_cast<const unsigned char*>("Wait:'W'"));
	glPopMatrix();
	/* 透視変換行列の設定 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	
	glOrtho(-30,30,-30,30,-30,30);
	//gluPerspective(100.0 + wheel, (double)WIDTH / (double)HEIGHT, 1.0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//視点の設定
	gluLookAt(-10, -10, -25, 0, 0, 0, 0, 0, -1);
	/* 光源の位置設定 */
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
/*	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
	glLightfv(GL_LIGHT2, GL_POSITION, light2pos);
	glLightfv(GL_LIGHT3, GL_POSITION, light3pos);
	glLightfv(GL_LIGHT4, GL_POSITION, light4pos);
	glLightfv(GL_LIGHT5, GL_POSITION, light5pos);
	*///マテリアルの設定
	glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);


	/* 物体描写*/
	glPushMatrix();	
	//クォータニオンによる回転
	glMultMatrixd(Rotate);
	glTranslated(-30, -30, -30);
	glPushMatrix();//粒子描写
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
	
	
	i = time-1;
	
	for (int j = 0; j < step[i + 1].count; j++)
	{
		circle(step[i + 2].pos[j].x*30,step[i + 2].pos[j].y*30,
			step[i + 2].pos[j].z*30, (step[i + 2].pos[j].r)/20
			);
	}
	glPopMatrix();

	
	glPushMatrix();//箱描写
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
	glTranslated(0, 0, 18);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{	seihoukei(10, 10, 12);
		glTranslated(10, 0, 0);
	}
		glTranslated(-30, 0, 0);
		seihoukei(10, 10, 12);
		glTranslated(0, 10, 0);
	}
	glPopMatrix();
	
	glPushMatrix();//枠描写
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, black);
	sikaku(30, 30, 30);
	glPopMatrix();

	
	glPopMatrix();
	
	glutSwapBuffers();

	//}
}

void resize(int w, int h)
{

}


void idle(void)
{
	glutPostRedisplay();
}

void Init(){
	glClearColor(1, 1, 1, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT3);
	glEnable(GL_LIGHT4);
	glEnable(GL_LIGHT5);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH_HINT);
	glLoadIdentity();
	qtor(Rotate, current);

}

void mousemove(int x, int y)
{

	//移動量を計算
	double dx = (x - Mouse_X) * 1.33 / WIDTH;
	double dy = (y - Mouse_Y) * 1.0 / HEIGHT;

	//クォータニオンの長さ
	double length = sqrt(dx * dx + dy * dy);

	if (length != 0.0)
	{
		double radian = length * PAI;
		double theta = sin(radian) / length;
		Quaternion after = { cos(radian), dy * theta, dx * theta, 0.0 };//回転後の姿勢

		Target = after * current;

		qtor(Rotate, Target);
	}



}

void mouse(int button, int state, int x, int y)
{
	if (button)
	{
		switch (state){
		case GLUT_DOWN://マウスボタンを押した場合、そこの位置を記憶
			Mouse_X = x;
			Mouse_Y = y;
			break;
		case GLUT_UP://マウスボタンを話した場合、姿勢を保存
			current = Target;
			break;
		default:
			break;
		}
	}

}


void MouseWheel(int wheel_number, int direction, int x, int y)
{
	if (direction == 1){ wheel++; }
	else{ wheel--; }
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':  /* '\033' は ESC の ASCII コード */
		exit(0);
		break;
	case 'g':
			timecheck = 0;
			break;
		case'b':
			timecheck = 1;
			break;
		case'w':
				timecheck = 2;
			break;
	default:
		break;
	}
}

void timer(int value) {
	
	if (timecheck == 0)
	{
		time += 1;
	}
	if (timecheck ==1)
	{
		time -= 1;
	}

	glutPostRedisplay();
	glutTimerFunc(500, timer, 0);
}

int main(int argc, char *argv[])
{
	file_read("output.txt");
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("排気ガスシミュレーション");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemove);
	glutMouseWheelFunc(MouseWheel);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutTimerFunc(500, timer, 0);
	Init();
	glutMainLoop();
	return 0;
}