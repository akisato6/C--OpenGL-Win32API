#pragma warning (disable : 4996) 

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<GL/freeglut.h>
#include <math.h>


#define WIDTH 420
#define HEIGHT 240
#define PAI 3.14159


int fcount = 0;
float vxmax = 0;
float vymax = 0;
float vzmax = 0;
float gx = 0;
float gy = 0;
float gz = 0;
float gZoom = 4;
GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };
GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };
float a = 0;
float b = 0;

GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat red[] = { 0.8, 0.2, 0.2, 1.0 };
//オレンジ
GLfloat orange[] = { 1.0f, 0.6f, 0.0f, 1.0f };
//ライトの位置
GLfloat lightpos[] = { 200.0, 150.0, -500.0, 1.0 };

int Mouse_X, Mouse_Y;

typedef struct {
	float x, y, z;
	int fa1, fb1, fa2, fb2, fa3, fb3;
	char name[10000];
}PositionV, PositionVn;
PositionV posv[10000];
PositionVn posvn[10000];

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
	int q = 0;

	

	//視点の設定
	gluLookAt(30, 30, -10+gZoom, //カメラの座標
		0, 0, 0, // 注視点の座標
		0.0, 1.0, 0.0); // 画面の上方向を指す



	//クォータニオンによる回転
	glMultMatrixd(Rotate);
	//ライトの設定
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	//マテリアルの設定
	glMaterialfv(GL_FRONT, GL_DIFFUSE, orange);
	glutSolidCube(10);

	/*for (q = 0; q < fcount; q++)
	{
		glNormal3f(posvn[posv[q].fb1].x, posvn[posv[q].fb2].y, posvn[posv[q].fb3].z);
	
		triangles(posv[posv[q].fa1].x , posv[posv[q].fa1].y , posv[posv[q].fa1].z,
			posv[posv[q].fa2].x , posv[posv[q].fa2].y, posv[posv[q].fa2].z
			, posv[posv[q].fa3].x , posv[posvn[q].fa3].y, posv[posvn[q].fa3].z );
	}*/
	
	glutSwapBuffers();
}


void idle(void)
{
	glutPostRedisplay();
}

void Init(){
	glClearColor(1, 1, 1, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	qtor(Rotate, current);

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
void resize(int w, int h)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/*glOrtho(gx-100, gx+100, gy-100, gy+100, gz-100, gz+100);
	*/


}
void wheel(int wheel_number, int direction, int x, int y){
	gZoom -= (float)direction*0.1;
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	map_read("rightarm1.txt");
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 440);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("クォータニオンで自由軸回転");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemove);
	glutMouseWheelFunc(wheel);

	glutIdleFunc(idle);
	Init();
	glutMainLoop();
	return 0;
}
