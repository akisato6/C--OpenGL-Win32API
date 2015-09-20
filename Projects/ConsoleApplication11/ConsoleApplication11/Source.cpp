#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <GL/freeglut.h>
#include <math.h>

#define WIDTH 600
#define HEIGHT 440
#define PAI 3.14159


#pragma warning (disable : 4996) 
int fcount = 0;
float vxmax = 0;
float vymax = 0;
float vzmax = 0;
float gx = 0;
float gy = 0;
float gz = 0;
float a = 0;
float b = 0;
float wheel;
float lightx = 0;
float lighty = 0;
float lightz = 0;


GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };
GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };
GLfloat blue[] = { 0, 0, 1, 1 };
GLfloat orange[] = { 1.0f, 0.6f, 0.0f, 1.0f };
GLfloat lightpos1[] = { 10.0, 10.0, 10.0, 1.0 };
GLfloat lightpos2[] = { -12.0, -15.0, -15.0, 1.0 };
int Mouse_X, Mouse_Y,Mouse_judge;

typedef struct 
{
	float x, y, z;
	int fv1, fvn1, fv2, fvn2, fv3, fvn3;
	char name[10000];
}PositionV, PositionVn;

PositionV v[10000];
PositionVn vn[10000];

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

void points(float x, float y, float z)
{
	glColor3f(0, 1.0, 1.0);
	float pointsize = 0.1;
	glPointSize(pointsize);

	glBegin(GL_POINTS);
	glVertex3f(x, y, z);
	glEnd();
}

void line(float x1, float y1,float z1, float x2, float y2,float z2)
{
	
	float pointsize = 0.5;
	glPointSize(pointsize);

	glBegin(GL_LINES);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2,z2);
	glEnd();
}

void linebody(float x1, float y1, float z1, float x2, float y2, float z2,float x3,float y3,float z3)
{

	float pointsize = 0.5;
	glPointSize(pointsize);

	glBegin(GL_LINE_LOOP);
	glVertex3d(x1, y1, z1);
	glVertex3d(x2, y2, z2);
	glVertex3d(x3, y3, z3);
	glEnd();
}

void *font = GLUT_BITMAP_HELVETICA_18;



int file_read(char *filename)
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

				sscanf(buf + 2, "%f %f %f", &v[i].x, &v[i].y, &v[i].z);

				if (vxmax < fabsf(v[i].x))
				{
					vxmax = fabsf(v[i].x);
				}
				if (vymax < fabsf(v[i].y))
				{
					vymax = fabsf(v[i].y);
				}
				if (vzmax < fabsf(v[i].z))
				{
					vzmax = fabsf(v[i].z);
				}
				gx = gx + v[i].x;
				gy = gy + v[i].y;
				gz = gz + v[i].z;
				i++;
				break;

			case 'n':

				sscanf(buf + 3, "%f %f %f", &vn[j].x, &vn[j].y, &vn[j].z);

				++j;
				break;

			}

			break;
		case 'f':
			sscanf(buf + 2, "%d//%d %d//%d %d//%d", &v[k].fv1, &v[k].fvn1, &v[k].fv2, &v[k].fvn2, &v[k].fv3, &v[k].fvn3);
			/*printf("f %d//%d %d//%d %d//%d\n", posv[k].fa1, posv[k].fb1, posv[k].fa2, posv[k].fb2, posv[k].fa3, posv[k].fb3);
			*/++k;
			break;


		case 'g':

			sscanf(buf + 2, "%s", v[0].name);
			/*printf("g %s\n", v[0].name);*/
			break;

		case'u':

			sscanf(buf + 6, "%s", vn[0].name);
			/*	printf("usemtl %s\n", posvn[0].name);*/
			break;
		default:
			break;
		}



		fcount = k;

	}
	printf("比 %f %f %f\n", vxmax, vymax, vzmax);
	printf("f %d\n", k);

	vzmax = vxmax;

	gx = gx / (i*vzmax);
	gy = gy / (i*vzmax);
	gz = gz / (i*vzmax);
	printf("X%f Y%f Z%f\n", gx, gy, gz);
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

	float t = -0.8;
	int q = 0;
	static int r = 0; /* 回転角 */

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, WIDTH, HEIGHT);

	/* 透視変換行列の設定 */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(20 + wheel, (double)WIDTH / (double)HEIGHT, 1.0, 100.0);
	/*glOrtho(gx-100, gx+100, gy-100, gy+100, gz-100, gz+100);
	*/
	/* モデルビュー変換行列の設定 */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//視点の設定
	gluLookAt( 1,1, 2, 0,0, 0, 0, 1, 1);

	//ライトの位置設定
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);
	
	/* モデルビュー変換行列の保存 */
	glPushMatrix();

	//クォータニオンによる回転
	glMultMatrixd(Rotate);
	glTranslatef(a-b, 0, 0);
	
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);



	glRasterPos3d(0.4, 0, 0);//0,0,0位置をスタート位置にする
	glutBitmapString(font, reinterpret_cast<const unsigned char*>("X"));
	glRasterPos3d(0.1, 0.3, 0);//0,0,0位置をスタート位置にする
	glutBitmapString(font, reinterpret_cast<const unsigned char*>("Y"));
	glRasterPos3d(0.1, 0, 0.3);//0,0,0位置をスタート位置にする
	glutBitmapString(font, reinterpret_cast<const unsigned char*>("Z"));

	glColor3f(1, 0, 0);
	line(0.1, 0, 0, 0.4, 0, 0);
	glColor3f(0.3, 1, 0);
	line(0.1, 0, 0, 0.1, 0.3, 0);
	glColor3f(0, 0, 1);
	line(0.1, 0, 0, 0.1, 0, 0.3);
	
	/*for (q = 0; q < 2233; q++)
	{

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
		glNormal3f(vn[(v[q].fvn1) - 1].x, vn[(v[q].fvn2) - 1].y, vn[(v[q].fvn3) - 1].z); 
		points(v[q].x / (vzmax)-gx, v[q].y / (vzmax)-gy, v[q].z / (vzmax)-gz);
	}*/
	
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
	
	for (q = 0; q < fcount; q++)
	{
		
		
		lightx = (vn[(v[q].fvn1) - 1].x + vn[(v[q].fvn2) - 1].x + vn[(v[q].fvn3) - 1].x)/3;
		lighty = (vn[(v[q].fvn1) - 1].y + vn[(v[q].fvn2) - 1].y + vn[(v[q].fvn3) - 1].y) / 3;
		lightz = (vn[(v[q].fvn1) - 1].z + vn[(v[q].fvn2) - 1].z + vn[(v[q].fvn3) - 1].z) / 3;

		glNormal3f(lightx, lighty, lightz);

		/*glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, orange);
	linebody(v[(v[q].fv1) - 1].x / (vzmax)-gx, v[(v[q].fv1) - 1].y / (vzmax)-gy, v[(v[q].fv1) - 1].z / (vzmax)-gz,
		v[(v[q].fv2 - 1)].x / (vzmax)-gx, v[(v[q].fv2) - 1].y / (vzmax)-gy, v[(v[q].fv2) - 1].z / (vzmax)-gz,
			v[(v[q].fv3) - 1].x / (vzmax)-gx, v[(v[q].fv3) - 1].y / (vzmax)-gy, v[(v[q].fv3) - 1].z / (vzmax)-gz);
			*/
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, red);
		
		
		triangles(v[(v[q].fv1) - 1].x / (vzmax)-gx, v[(v[q].fv1) - 1].y/ (vzmax)-gy, v[(v[q].fv1) - 1].z/ (vzmax)-gz,
			v[(v[q].fv2 - 1)].x/ (vzmax)-gx, v[(v[q].fv2) - 1].y / (vzmax)-gy, v[(v[q].fv2) - 1].z / (vzmax)-gz,
			v[(v[q].fv3) - 1].x/ (vzmax)-gx, v[(v[q].fv3) - 1].y/ (vzmax)-gy, v[(v[q].fv3) - 1].z / (vzmax)-gz);

	}
	glPopMatrix();
	glutSwapBuffers();
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
	glLightfv(GL_LIGHT0, GL_DIFFUSE, red);
	glLightfv(GL_LIGHT1, GL_SPECULAR, red);

	qtor(Rotate, current);

}

void mousemove(int x, int y)
{
	if (Mouse_judge == 1)
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
	if (Mouse_judge == 2)
	{
		glTranslatef(10, 10, 1);
	}


}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		Mouse_judge = 1;
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
	if (button==GLUT_RIGHT_BUTTON)
	{
		Mouse_judge = 2;
		switch (state){
		case GLUT_DOWN:
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
	case 'a':
	case'A':
		a = a +0.1;
		break;
	case 'b':
	case'B':
		b = b + 0.1;
		break;
	default:
		break;
	}
}

int main(int argc, char *argv[])
{
	file_read("rightarm1.txt");
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("クォータニオンで自由軸回転");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMouseFunc(mouse);
	glutMotionFunc(mousemove);
	glutMouseWheelFunc(MouseWheel);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	Init();
	glutMainLoop();
	return 0;
}