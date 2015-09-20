#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#pragma warning (disable : 4996) 
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <GL/glut.h>
#include <math.h>

#define WIDTH 420
#define HEIGHT 240
#define PAI 3.14159

typedef struct {
	float x, y, z;
	int fa1, fb1, fa2, fb2, fa3, fb3;
	char name[10000];
}PositionV, PositionVn;


PositionV posv[10000];
PositionVn posvn[10000];

#pragma warning (disable : 4996) 
int fcount = 0;
float vxmax = 0;
float vymax = 0;
float vzmax = 0;
float gx = 0;
float gy = 0;
float gz = 0;
GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };
GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };
float a = 0;
float b = 0;
int Mouse_X, Mouse_Y;

GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };

void triangles(float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3)
{

	glBegin(GL_TRIANGLES);

	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x3, y3, z3);
	glEnd();

}


int map_read(char *filename)
{
	FILE *fp;
	char    buf[256];
	int i = 0;
	int j = 0;
	int k = 0;



	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("File %s is not created\n", filename);
		return 0;
	}

	while (fgets(buf, 1000, fp) != NULL)
	{
		/*printf("%s", buf);*/
		switch (buf[0])
		{
		case 'v':

			switch (buf[1])
			{
			case ' ':

				sscanf(buf + 2, "%f %f %f", &posv[i].x, &posv[i].y, &posv[i].z);
				/*	printf("v %f %f %f\n", posv[i].x, posv[i].y, posv[i].z);
				*/	if (vxmax<fabsf(posv[i].x))
				{
					vxmax = fabsf(posv[i].x);
				}
				if (vymax<fabsf(posv[i].y))
				{
					vymax = fabsf(posv[i].y);
				}
				if (vzmax<fabsf(posv[i].z))
				{
					vzmax = fabsf(posv[i].z);
				}
				gx = gx + posv[i].x;
				gy = gy + posv[i].y;
				gz = gz + posv[i].z;
				i++;
				break;

			case 'n':

				sscanf(buf + 3, "%f %f %f", &posvn[j].x, &posvn[j].y, &posvn[j].z);

				++j;
				break;

			}

			break;
		case 'f':
			sscanf(buf + 2, "%d//%d %d//%d %d//%d", &posv[k].fa1, &posv[k].fb1, &posv[k].fa2, &posv[k].fb2, &posv[k].fa3, &posv[k].fb3);
			/*printf("f %d//%d %d//%d %d//%d\n", posv[k].fa1, posv[k].fb1, posv[k].fa2, posv[k].fb2, posv[k].fa3, posv[k].fb3);
			*/++k;
			break;


		case 'g':

			sscanf(buf + 2, "%s", posv[0].name);
			/*printf("g %s\n", posv[0].name);*/
			break;

		case'u':

			sscanf(buf + 6, "%s", posvn[0].name);
			/*	printf("usemtl %s\n", posvn[0].name);*/
			break;
		default:
			break;
		}



		fcount = k;

	}
	printf("比 %f %f %f\n", vxmax, vymax, vzmax);
	printf("f %d\n", k);
	gx = gx / (i*vzmax);
	gy = gy / (i*vzmax);
	gz = gz / (i*vzmax);
	printf("X%f Y%f Z%f", gx, gy, gz);
	fclose(fp);	return 0;


}

void idle(void)
{
	glutPostRedisplay();
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




void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int q = 0;
	static int r = 0; /* 回転角 */



	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//視野角,アスペクト比(ウィンドウの幅/高さ),描画する範囲(最も近い距離,最も遠い距離)
	/*gluPerspective(30.0, (double)WIDTH / (double)HEIGHT, 1.0, 100.0);
	*/glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/* 視点位置と視線方向 */
	gluLookAt(gx + 1, gy + 1, gz + 1, gx, gy, gz, 0.0, 1.0, 0.0);

	//クォータニオンによる回転
	glMultMatrixd(Rotate);
	/* 光源の位置設定 */
	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1pos);


	/* 図形の色 (赤)  */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);

	for (q = 0; q < fcount; q++)
	{
		glNormal3f(posvn[posv[q].fb1].x, posvn[posv[q].fb2].y, posvn[posv[q].fb3].z);
		/*glColor3d(0,0, 0);*/
		triangles(posv[posv[q].fa1].x / (vzmax), posv[posv[q].fa1].y / (vzmax), posv[posv[q].fa1].z / (vzmax),
			posv[posv[q].fa2].x / (vzmax), posv[posv[q].fa2].y / (vzmax), posv[posv[q].fa2].z / (vzmax)
			, posv[posv[q].fa3].x / (vzmax), posv[posvn[q].fa3].y / (vzmax), posv[posvn[q].fa3].z / (vzmax));
	}

	glutSwapBuffers();

	/* 一周回ったら回転角を 0 に戻す */
	if (++r >= 360) r = 0;

}


void mousemove(int x, int y)
{
	//移動量を計算
	double dx = (x - Mouse_X) * 1.33 / WIDTH;
	double dy = (y - Mouse_Y) * 1.0 / HEIGHT;

	//クォータニオンの長さ
	double length = sqrt(dx * dx + dy * dy);

	if (length != 0.0) {
		double radian = length * PAI;
		double theta = sin(radian) / length;
		Quaternion after = { cos(radian), dy * theta, dx * theta, 0.0 };//回転後の姿勢

		Target = after * current;

		qtor(Rotate, Target);
	}
}
void mouse(int button, int state, int x, int y)
{
	if (button){
		switch (state){
		case GLUT_DOWN://マウスボタンを押した位置を記憶
			Mouse_X = x;
			Mouse_Y = y;
			break;
		case GLUT_UP://姿勢を保存
			current = Target;
			break;
		default:
			break;
		}
	}
}



void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':  /* '\033' は ESC の ASCII コード */
		exit(0);
	case 'a':
		a = a + 0.1;
		break;
	case'b':
		b = b + 0.1;
		break;
	}
}

void Init(){
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	qtor(Rotate, current);

}


int main(int argc, char *argv[])
{

	map_read("rightarm1.txt");

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 440);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);

	glutMouseFunc(mouse);
	glutMotionFunc(mousemove);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	Init();
	glutMainLoop();
	return 0;
}


