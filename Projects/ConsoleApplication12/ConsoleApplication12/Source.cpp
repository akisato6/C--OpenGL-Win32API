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

GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };
GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };




void printmath(float x, float y, float z,int math)
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

void tyouhoukei1(float x, float y, float z)
{

	int i = 0;
	GLdouble vertex1[][3] = {
		{ -x, -y, -z }, /* A */
		{ x, -y, -z }, /* B */
		{ x, y, -z }, /* C */
		{ -x, y, -z }, /* D */
		{ -x, -y, z }, /* E */
		{ x, -y, z }, /* F */
		{ x, y, z }, /* G */
		{ -x, y, z }  /* H */
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

	glBegin(GL_LINES);
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
		{ -6, -3, -6.3 }, /* A */
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

	glBegin(GL_POLYGON);
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
	glTranslated(x, y, z);
	glutSolidSphere(r, 16, 16);

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
	//for (i = 0; i < 30; i++)
	//{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, WIDTH, HEIGHT);
		/* 透視変換行列の設定 */
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(100.0 + wheel, (double)WIDTH / (double)HEIGHT, 1.0, 100.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//視点の設定
		gluLookAt(30, 30, 16, 0, 0, 0, 0.0, 1, 0);

		/* 光源の位置設定 */
		glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
		glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
		//マテリアルの設定
		glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);


		glRasterPos3d(-12.5, 9, 11.6);
		glutBitmapString(font, reinterpret_cast<const unsigned char*>("Step     :"));
		glRasterPos3d(-12, 8, 12);
		glutBitmapString(font, reinterpret_cast<const unsigned char*>("Particle :"));
		int Step = 100;
		int Particle = 40;
		printmath(-11, 8.7, 8, Step);
		printmath(-9.3, 8.4, 8.5, Particle);



		/* モデルビュー変換行列の保存 */
		glPushMatrix();
		//クォータニオンによる回転
		glMultMatrixd(Rotate);

		glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);


		for (int j = 0; j < step[i + 1].count; j++)
		{
			circle(step[i + 2].pos[j].x, 30 * step[i + 2].pos[j].y,
				30 * step[i + 2].pos[j].z, step[i + 2].pos[j].r
				);
		}

		/*
		*/
		glPopMatrix();

		/* 図形の描画 */

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
		tyouhoukei1(6, 3, 6);

		for (i = 0; i < 4; i++)
		{
			glColor3d(1.0, 0.0, 0.0);
			tyouhoukei2();
			glTranslatef(0, 0, 4);

		}

		for (i = 0; i < 4; i++)
		{
			glColor3d(1.0, 0.0, 0.0);
			tyouhoukei3();
			glTranslatef(4, 0, 0);
		}
		/* モデルビュー変換行列の復帰 */
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
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH_HINT);
	
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
	glutIdleFunc(idle);
	Init();
	glutMainLoop();
	return 0;
}