#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"glut.h"
#pragma warning(disable:4996)
#define NAME "DLC Film Formation Simulator"
#define AR_NUMBER 10000							// Max number of Ar ion particles.
#define DLC_NUMBER 40000						// Max number of DLC particles.
#define AR_RADIUS 1.0							// Radius of Ar ion.
#define DLC_RADIUS 2.0							// Radius of DLC particle.
//#define CV 60.0									// Color value

typedef struct{
	float x, y, z, r;
	int b, c;
}Position;

typedef struct
{

	Position pos[3000];
	int step, particle;
	char name[1000];
	int count;
}Step;

Step step[32];


typedef struct{
	float x, y, z, r;
	float dx, dy, dz;
} PARTICLE;

typedef struct{
	double sput_rate;
	double beam_spd;
	double beam_agl;
	double Ar_gene_num;

	int CVS_step_num, Sp_step_num;
	double deltat;
	double sizex, sizey, sizez;

	int meshx, meshy, meshz;
	double fill_param;
	int mesh_elevation;

	int Ar_num, DLC_num;
	int mesh_gap, output_gap;
	double mh;
} MODEL;

typedef struct{
	double zparameter_1,zparameter_2;
	int cellnumber;
	double cellspan;
	double wallthickness;
	int mushnumber_x,mushnumber_y,mushnumber_z;
	double judgecondition;
	int stepnum;
	int gene_rate;
	double radius;
	double deltat;
	int outputgap;
	int meshcalcgap;
	double meanradius;
	double variance;
	int frequency;
	double flow_x, flow_y, flow_z;
	double bordertemp;
	int tempmesh_1, tempmesh_2;
	double temperture;

} Deta;


typedef struct{		//Parameter for display.
	int curstep,		//Current Step.
		pnum;			//numbers of particles of the specific step.
	double viewpos[4];	//View position(0:distance 1:twist 2:elevation 3:azimuth)
	int rend_part;		//Parameter of rendering parameter or not.
	// 0: Do not render particles. 1: Render particles.
	int depo_mode;		// Deposition mode.
	// 0: Mesh   1:Wire 2Surface
	int view_mode;		// 0: Normal 1: Measure
	int Render;			// 0: CVD+Sp 1: CVD only
	int moviespeed;
} D_PARAM;

typedef struct{		//Parameter for mouse
	int button;			//Type of button
	int xstart, ystart; //Coordinate parameter.
	int mode;
} M_PARAM;

MODEL model;
Deta deta;
PARTICLE Ar[AR_NUMBER], DLC[DLC_NUMBER];
double *imesh, *mesh, *mesh2;
D_PARAM disp;
M_PARAM mous;


void seihoukei(float x, float y, float z)
{
	float pointsize = 9;
	glPointSize(pointsize);
	
	/*glBegin(GL_POINTS);
	glNormal3f(0, -1.0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(x, 0, 0);
	glVertex3d(x, 0, z);
	glVertex3d(0, 0, z);
	glEnd();
	*/
	glPointSize(pointsize);
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, z);
	glVertex3d(0, y, z);
	glVertex3d(0, y, 0);
	glEnd();
	
	/*glPointSize(pointsize);
	glBegin(GL_POINTS);
	glNormal3f(0, 1.0, 0);
	glVertex3d(0, y, 0);
	glVertex3d(0, y, z);
	glVertex3d(x, y, z);
	glVertex3d(x, y, 0);
	glEnd();
	*/
	glPointSize(pointsize);
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0, 0);
	glVertex3d(x, 0, 0);
	glVertex3d(x, 0, z);
	glVertex3d(x, y, z);
	glVertex3d(x, y, 0);
	glEnd();
	
	glPointSize(pointsize);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1.0);
	glVertex3d(0, 0, z);
	glVertex3d(x, 0, z);
	glVertex3d(x, y, z);
	glVertex3d(0, y, z);
	glEnd();
	glPointSize(pointsize);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1.0);
	glVertex3d(0, 0, 0);
	glVertex3d(x, 0, 0);
	glVertex3d(x, y, 0);
	glVertex3d(0, y, 0);
	glEnd();
	
}

void circle(float x, float y, float z, float r)
{
	glPushMatrix();
	glTranslated(x, y, z);
	glutSolidSphere(r, 16, 16);
	glPopMatrix();
}

void Polarview(D_PARAM *disp)
{
	glTranslatef(0.0, 0.0, disp->viewpos[0]);
	glRotatef(-(disp->viewpos[1]), 0.0, 0.0, 1.0);
	glRotatef(-(disp->viewpos[2]), 1.0, 0.0, 0.0);
	glRotatef(-(disp->viewpos[3]), 0.0, 1.0, 0.0);
}

void glwirecube(double xa, double xb, double ya, double yb, double za, double zb)
{
	glBegin(GL_LINE_LOOP);
	glVertex3d(xa, ya, za);
	glVertex3d(xb, ya, za);
	glVertex3d(xb, yb, za);
	glVertex3d(xa, yb, za);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(xa, ya, za);
	glVertex3d(xb, ya, za);
	glVertex3d(xb, ya, zb);
	glVertex3d(xa, ya, zb);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(xa, ya, za);
	glVertex3d(xa, ya, zb);
	glVertex3d(xa, yb, zb);
	glVertex3d(xa, yb, za);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(xb, yb, zb);
	glVertex3d(xa, yb, zb);
	glVertex3d(xa, yb, za);
	glVertex3d(xb, yb, za);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(xb, yb, zb);
	glVertex3d(xb, ya, zb);
	glVertex3d(xa, ya, zb);
	glVertex3d(xa, yb, zb);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex3d(xb, yb, zb);
	glVertex3d(xb, ya, zb);
	glVertex3d(xb, ya, za);
	glVertex3d(xb, yb, za);
	glEnd();
}

void glcube(double xa, double xb, double ya, double yb, double za, double zb)
{
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3d(xa, ya, za);
	glVertex3d(xa, yb, za);
	glVertex3d(xb, yb, za);
	glVertex3d(xb, ya, za);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3d(xa, ya, za);
	glVertex3d(xb, ya, za);
	glVertex3d(xb, ya, zb);
	glVertex3d(xa, ya, zb);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3d(xa, ya, za);
	glVertex3d(xa, ya, zb);
	glVertex3d(xa, yb, zb);
	glVertex3d(xa, yb, za);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3d(xb, yb, zb);
	glVertex3d(xb, yb, za);
	glVertex3d(xa, yb, za);
	glVertex3d(xa, yb, zb);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3d(xb, yb, zb);
	glVertex3d(xa, yb, zb);
	glVertex3d(xa, ya, zb);
	glVertex3d(xb, ya, zb);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3d(xb, yb, zb);
	glVertex3d(xb, ya, zb);
	glVertex3d(xb, ya, za);
	glVertex3d(xb, yb, za);
	glEnd();
}

void glprint(char *mode, char *sentence)
{
	int i = 0;
	glPushMatrix();

	if (strcmp(mode, "roman") == 0){
		while (sentence[i] != '\0'){
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, sentence[i]);
			i++;
		}
	}
	else if (strcmp(mode, "bitmap") == 0){
		while (sentence[i] != '\0'){
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, sentence[i]);
			i++;
		}
	}
	else if (strcmp(mode, "stroke") == 0){
		glScaled(0.01, 0.01, 0.01);
		while (sentence[i] != '\0'){
			glutStrokeCharacter(GLUT_STROKE_ROMAN, sentence[i]);
			i++;
		}
	}
	else printf("Error !");

	glPopMatrix();
}

void SetglColor(double velocity, MODEL *m){

	if (velocity>m->mh) velocity = m->mh;
	velocity /= m->mh;

	if (velocity <= 0.25) glColor3d(0.0, 4.0*velocity, 1.0);
	else if (velocity <= 0.5) glColor3d(0.0, 1.0, 1.0 - 4.0*(velocity - 0.25));
	else if (velocity <= 0.75) glColor3d(4.0*(velocity - 0.5), 1.0, 0.0);
	else glColor3d(1.0, 1.0 - 4.0*(velocity - 0.75), 0.0);
}


/*
*	Load data from "input.txt".
*/


int loadfile(Deta *deta){
	FILE *fp;
	char buf[1024];

	// **** Load data from "input.txt". ****
	puts("Loading data...");
	if ((fp = fopen("endat.txt", "r")) == NULL){
		puts("Could not open the file \"endat.txt\".");
		exit(1);
	}

	while (fgets(buf, 1024, fp) != NULL){
		if (!strncmp("zparameter:", buf, 11)) sscanf(buf, "%*s %lf %lf", &(deta->zparameter_1), &(deta->zparameter_2));
		else if (!strncmp("cellnumber:", buf, 11)) sscanf(buf, "%*s %d", &(deta->cellnumber));
		else if (!strncmp("cellspan:", buf, 9)) sscanf(buf, "%*s %lf", &(deta->cellspan));
		else if (!strncmp("wallthickness:", buf, 14)) sscanf(buf, "%*s %lf", &(deta->wallthickness));
		else if (!strncmp("meshnumber:", buf, 11)) sscanf(buf, "%*s %lf %lf %lf", &(deta->mushnumber_x), &(deta->mushnumber_y), &(deta->mushnumber_z));
		
		else if (!strncmp("judgecondition:", buf, 15)) sscanf(buf, "%*s %f", &(deta->judgecondition));
		else if (!strncmp("stepnum:", buf, 8)) sscanf(buf, "%*s %d", &(deta->stepnum));

		else if (!strncmp("gene_rate:", buf, 10)) sscanf(buf, "%*s %lf", &(deta->gene_rate));
		else if (!strncmp("radius:", buf, 7)) sscanf(buf, "%*s %lf", &(deta->radius));
		else if (!strncmp("deltat:", buf, 7)) sscanf(buf, "%*s %lf", &(deta->deltat));
		else if (!strncmp("outputgap:", buf, 10)) sscanf(buf, "%*s %d", &(deta->outputgap));
		else if (!strncmp("meshcalcgap:", buf, 12)) sscanf(buf, "%*s %d", &(deta->meshcalcgap));
		else if (!strncmp("meanradius:", buf, 11)) sscanf(buf, "%*s %lf", &(deta->meanradius));


		else if (!strncmp("variance:", buf, 8)) sscanf(buf, "%*s %lf", &(deta->variance));
		else if (!strncmp("frequency:", buf, 9)) sscanf(buf, "%*s %d", &(deta->frequency));
		else if (!strncmp("flow:", buf, 5)) sscanf(buf, "%*s %lf lf lf", &(deta->flow_x), &(deta->flow_y), &(deta->flow_z));
		else if (!strncmp("bordertemp:", buf, 11)) sscanf(buf, "%*s %lf", &(deta->bordertemp));
		else if (!strncmp("tempmesh:", buf, 9)) sscanf(buf, "%*s %d %d", &(deta->tempmesh_1), &(deta->tempmesh_2));
		else if (!strncmp("temperture:", buf, 11)) sscanf(buf, "%*s %lf", &(deta->temperture));



	}

	fclose(fp);

	// **** Output loaded data from "input.txt". ****
	printf("zparameter        : %9.2lf  %9.2lf\n", deta->zparameter_1, deta->zparameter_2);
	printf("cellnumber        : %6d\n", deta->cellnumber);
	printf("cellspan          : %9.2lf\n", deta->cellspan);
	printf("wllthickness      : %9.2lf\n", deta->wallthickness);
	/*printf("Step number(CVS)       : %6d\n", data->CVS_step_num);
	printf("Step number(Sp)        : %6d\n", data->Sp_step_num);
	printf("Time variation[sec]    : %9.2lf\n", data->deltat);
	printf("Size of model[nm]      : %9.2lf  %9.2lf  %9.2lf\n", model->sizex, model->sizey, model->sizez);
	printf("Mesh division          : %6d     %6d     %6d\n", model->meshx, model->meshy, model->meshz);
	printf("Mesh fill parameter[%%] : %9.2lf\n", model->fill_param);
	printf("Mesh calculation gap   : %6d\n", model->mesh_gap);
	printf("Result output gap      : %6d\n", model->output_gap);
	printf("Max height             : %9.2lf\n", model->mh);
	*/
	return 0;
}


int loaddata(MODEL *model){
	FILE *fp;
	char buf[1024];

	// **** Load data from "input.txt". ****
	puts("Loading data...");
	if ((fp = fopen("input.txt", "r")) == NULL){
		puts("Could not open the file \"input.txt\".");
		exit(1);
	}

	while (fgets(buf, 1024, fp) != NULL){
		if (!strncmp("Sputtering_rate:", buf, 16)) sscanf(buf, "%*s %lf", &(model->sput_rate));
		else if (!strncmp("Beam_speed[nm/s]:", buf, 17)) sscanf(buf, "%*s %lf", &(model->beam_spd));
		else if (!strncmp("Beam_angle[deg]:", buf, 16)) sscanf(buf, "%*s %lf", &(model->beam_agl));
		else if (!strncmp("Ar_ion_number[qty/sec]:", buf, 23)) sscanf(buf, "%*s %lf", &(model->Ar_gene_num));
		else if (!strncmp("CVD_Step_number:", buf, 16)) sscanf(buf, "%*s %d", &(model->CVS_step_num));
		else if (!strncmp("Sp_Step_number:", buf, 15)) sscanf(buf, "%*s %d", &(model->Sp_step_num));
		else if (!strncmp("Time_variation[sec]:", buf, 20)) sscanf(buf, "%*s %lf", &(model->deltat));
		else if (!strncmp("Model_size[nm]_(x,y,z):", buf, 23)) sscanf(buf, "%*s %lf %lf %lf", &(model->sizex), &(model->sizey), &(model->sizez));
		else if (!strncmp("Mesh_division_(x,y,z):", buf, 22)) sscanf(buf, "%*s %d %d %d", &(model->meshx), &(model->meshy), &(model->meshz));
		else if (!strncmp("Mesh_fill_parameter[%]:", buf, 23)) sscanf(buf, "%*s %lf", &(model->fill_param));
		else if (!strncmp("Mesh_calculation_gap:", buf, 21)) sscanf(buf, "%*s %d", &(model->mesh_gap));
		else if (!strncmp("Result_output_gap:", buf, 18)) sscanf(buf, "%*s %d", &(model->output_gap));
		else if (!strncmp("Max_height:", buf, 10)) sscanf(buf, "%*s %lf", &(model->mh));
	}

	fclose(fp);

	// **** Output loaded data from "input.txt". ****
	printf("Sputtering Rate        : %9.2lf\n", model->sput_rate);
	printf("Beam speed[nm/s]       : %9.2lf\n", model->beam_spd);
	printf("Beam angle[deg]        : %9.2lf\n", model->beam_agl);
	printf("Ar ion number[qty/sec] : %9.2lf\n\n", model->Ar_gene_num);
	printf("Step number(CVS)       : %6d\n", model->CVS_step_num);
	printf("Step number(Sp)        : %6d\n", model->Sp_step_num);
	printf("Time variation[sec]    : %9.2lf\n", model->deltat);
	printf("Size of model[nm]      : %9.2lf  %9.2lf  %9.2lf\n", model->sizex, model->sizey, model->sizez);
	printf("Mesh division          : %6d     %6d     %6d\n", model->meshx, model->meshy, model->meshz);
	printf("Mesh fill parameter[%%] : %9.2lf\n", model->fill_param);
	printf("Mesh calculation gap   : %6d\n", model->mesh_gap);
	printf("Result output gap      : %6d\n", model->output_gap);
	printf("Max height             : %9.2lf\n", model->mh);

	return 0;
}

/*
*	Load data from "output.txt".
*/



int loadresult(MODEL *model, PARTICLE Ar[], PARTICLE DLC[], D_PARAM *disp)
{
	FILE *fp;
	char    buf[256];
	int i = 0;
	int j = 0;
	int k = 0;
	int count = 0;
	fp = fopen("output.txt", "r");
	if ((fp = fopen("output.txt", "r")) == NULL) {
		puts("Cannot open the file \"output.txt\".");
		exit(-1);
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


int loadmeshdata(char *filename, MODEL *model, double mesh[], D_PARAM *disp){
	FILE *fp;
	int i, step, flag = 0, loadstep;
	char buf[256];

	if ((fp = fopen(filename, "r")) == NULL) {
		printf("Cannot open the file \"%s\".", filename);
		exit(-1);
	}

	if (disp->Render && disp->curstep>model->CVS_step_num) loadstep = model->CVS_step_num;
	else loadstep = disp->curstep;

	while (fgets(buf, 256, fp) || flag == 1){
		if (strncmp(buf, "STEP:", 5) != 0) continue;
		sscanf(buf, "%*s %d", &step);
		if (step == loadstep){
			sscanf(buf, "%*s %*d %d", &(model->mesh_elevation));
			break;
		}
	}

	for (i = 0; i<model->meshx*model->meshy; i++) fscanf(fp, "%lf", &mesh[i]);

	fclose(fp);

	return 0;
}

int InitDispParam(MODEL *model, D_PARAM *disp){
	disp->curstep = 0;
	disp->pnum = 0;
	disp->viewpos[0] = -1.5*(model->sizex + model->sizey + model->sizez);
	disp->viewpos[1] = 0.0;
	disp->viewpos[2] = -12.5;
	disp->viewpos[3] = -105.0;
	disp->moviespeed = 1;
	disp->rend_part = 1;
	disp->depo_mode = 0;
	disp->view_mode = 0;
	disp->Render = 0;
	printf("mov:%d\n", disp->moviespeed);

	imesh = (double *)malloc(sizeof(double)*model->meshx*model->meshy);
	mesh = (double *)malloc(sizeof(double)*model->meshx*model->meshy);
	mesh2 = (double *)malloc(sizeof(double)*model->meshx*model->meshy);

	loadmeshdata("meshdata.txt", model, imesh, disp);

	disp->curstep = model->CVS_step_num;
	loadmeshdata("meshdata.txt", model, mesh, disp);

	return 0;
}

/*
*	Render particles.
*/
int RenderParticles(MODEL *model, PARTICLE Ar[], PARTICLE DLC[], D_PARAM *disp){
	int i = 0;
	 i = disp->curstep/100;
	
	GLfloat	yellow[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat	gray[] = { 0.75, 0.75, 0.75, 1.0 };
	GLfloat green[] = { 0.30, 0.60, 0.30, 1.0 };

	if (disp->curstep <= model->CVS_step_num) glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gray);
	
	else glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
	
	for (int j = 0; j < step[i ].count; j++)
	{
		circle(step[i+1].pos[j].y * 500, 300-(step[i+1].pos[j].z * 400),
			step[i+1].pos[j].x * 500, (step[i+1].pos[j].r) 
			);
	}

	return 0;
}

/*
*	Render solid carbon.
*/
int RenderSolidCarbon(MODEL *model){
	GLfloat gray[] = { 0.50, 0.50, 0.50, 1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gray);
	glcube(500.0, model->sizey, model->sizez + 5.0, model->sizez, 0.0, model->sizex);

	return 0;
}

/*
*	Render basis.
*/
int RenderBasis(MODEL *model){

	glPushMatrix();	
	GLfloat skyblue[] = { 0.30, 0.30, 0.90, 1.0 };

	
//	glcube(0.0, model->sizey, 0.0, -5.0, 0.0, model->sizex);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, skyblue);
	
	glPushMatrix();
	for (int j = 0; j <deta.cellnumber+1; j++)
	{
		glcube(0, 500, 0, 100, -deta.wallthickness / 2, deta.wallthickness/2);
		//	glcube(-5, 5, 0, 100, 0, 500);
		//glcube(0, 167, 0, 100, 0, 167);
		glTranslated(0, 0, (500/deta.cellnumber));
	}
	glPopMatrix();
	glPushMatrix();
	for (int i = 0; i < deta.cellnumber+1; i++)
	{
		
		
		glcube(-deta.wallthickness / 2, deta.wallthickness / 2, 0, 100, 0, 500);
		
		glTranslated((500/deta.cellnumber),0 , 0);
	}
	
	glPopMatrix();

	glPopMatrix();
	



	return 0;
}

/*
*	Render basis.
*/


void glMyCubeMesh(MODEL* m, double xa, double xb, double ya, double yb, double za, double zb){
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, -1.0);
	SetglColor(yb, m);
	glVertex3d(xa, yb, za);
	glVertex3d(xb, yb, za);
	SetglColor(ya, m);
	glVertex3d(xb, ya, za);
	glVertex3d(xa, ya, za);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0, 0.0);
	SetglColor(ya, m);
	glVertex3d(xa, ya, za);
	glVertex3d(xb, ya, za);
	glVertex3d(xb, ya, zb);
	glVertex3d(xa, ya, zb);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(-1.0, 0.0, 0.0);
	SetglColor(ya, m);
	glVertex3d(xa, ya, za);
	glVertex3d(xa, ya, zb);
	SetglColor(yb, m);
	glVertex3d(xa, yb, zb);
	glVertex3d(xa, yb, za);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, -1.0, 0.0);
	SetglColor(yb, m);
	glVertex3d(xb, yb, zb);
	glVertex3d(xb, yb, za);
	glVertex3d(xa, yb, za);
	glVertex3d(xa, yb, zb);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0.0, 0.0, 1.0);
	SetglColor(yb, m);
	glVertex3d(xb, yb, zb);
	glVertex3d(xa, yb, zb);
	SetglColor(ya, m);
	glVertex3d(xa, ya, zb);
	glVertex3d(xb, ya, zb);
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1.0, 0.0, 0.0);
	SetglColor(ya, m);
	glVertex3d(xb, ya, zb);
	glVertex3d(xb, ya, za);
	SetglColor(yb, m);
	glVertex3d(xb, yb, za);
	glVertex3d(xb, yb, zb);
	glEnd();
}






/*
*	Render flame.
*/
int RenderFlame(MODEL *model){
	glDisable(GL_LIGHTING);
	glwirecube(0.0, model->sizey, -5.0, model->sizez + 200.0, 0.0, model->sizex);
	glEnable(GL_LIGHTING);
	return 0;
}

void Idle(void){
	disp.curstep += disp.moviespeed*model.output_gap;
	if (disp.curstep>model.CVS_step_num + model.Sp_step_num)
	{
		disp.curstep = model.CVS_step_num + model.Sp_step_num;
		disp.moviespeed = 0;
	}
	else if (disp.curstep<0){
		disp.curstep = 0;
		disp.moviespeed = 0;
	}
	glutPostRedisplay();
}

/*
*	Render data of simulation.
*/
int RenderText(D_PARAM *disp, MODEL *model){
	char string[64];

	sprintf(string, "Step     : %5d", disp->curstep/10);
	glRasterPos3d(0.05, 0.75, 0.0);
	glprint("bitmap", string);

	sprintf(string, "Particle : %5d", disp->curstep);
	glRasterPos3d(0.05, 0.50, 0.0);
	glprint("bitmap", string);
	return 0;
}

/*
*	Render buttons for video control.
*/
int RenderMenu(MODEL *model, D_PARAM *disp){
	/* Movie Menu */
	glBegin(GL_LINE_LOOP);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.0, 80.0, 0.0);
	glVertex3d(200.0, 80.0, 0.0);
	glVertex3d(200.0, 0.0, 0.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3d(0.0, 60.0, 0.0);
	glVertex3d(200.0, 60.0, 0.0);
	glVertex3d(0.0, 20.0, 0.0);
	glVertex3d(200.0, 20.0, 0.0);
	glVertex3d(70, 60, 0);
	glVertex3d(70, 20, 0);
	glVertex3d(130, 60, 0);
	glVertex3d(130, 20, 0);
	glVertex3d(20, 20, 0);
	glVertex3d(20, 0, 0);
	glVertex3d(180, 20, 0);
	glVertex3d(180, 0, 0);
	glEnd();
	/* Character */
	glBegin(GL_TRIANGLES);
	glVertex3d(155, 50, 0);
	glVertex3d(155, 30, 0);
	glVertex3d(175, 40, 0);
	glVertex3d(45, 50, 0);
	glVertex3d(45, 30, 0);
	glVertex3d(25, 40, 0);
	glVertex3d(15, 5, 0);
	glVertex3d(15, 15, 0);
	glVertex3d(5, 10, 0);
	glVertex3d(185, 5, 0);
	glVertex3d(185, 15, 0);
	glVertex3d(195, 10, 0);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3d(90, 50, 0);
	glVertex3d(90, 30, 0);
	glVertex3d(110, 30, 0);
	glVertex3d(110, 50, 0);
	glColor3d(0.3, 0.3, 0.3);
	glVertex3d(20, 0, -0.1);
	glVertex3d(20, 20, -0.1);
	glVertex3d(180, 20, -0.1);
	glVertex3d(180, 0, -0.1);
	glColor3d(1.0, 1.0, 1.0);
	glEnd();
	glPushMatrix();
	glTranslated((150 * (double)disp->curstep / (double)(model->CVS_step_num + model->Sp_step_num)) + 20, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3d(0, 20, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(10, 0, 0);
	glVertex3d(10, 20, 0);
	glEnd();
	glPopMatrix();
	glRasterPos3d(77, 65, 0);
	glprint("bitmap", "MOVIE");
	glColor3d(1.0, 1.0, 1.0);

	return 0;
}

/*
*	Display Function.
*	(Global vailiables used are, MODEL, D_PARAM and PARTICLE.)
*/
void Display(void){
	int width, height;
	
	
	// Load data of particles.
	loadresult(&model, Ar, DLC, &disp);
	loadmeshdata("meshdata.txt", &model, mesh2, &disp);

	// Render starts here.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);

	glViewport(0, 0, width, height);

	// アニメーションの描画 ------------------------------
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)width / (double)height, 2.9, 10000.0);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	Polarview(&disp);			// ポーラービュー設定
	
		glTranslatef(-0.5*(float)model.sizey, -0.5*(float)model.sizez, -0.5*(float)model.sizex);
		//RenderSolidCarbon(&model);		// カーボン描画
		RenderBasis(&model);			// 基盤の描画
		RenderFlame(&model);			// フレーム描画
		 RenderParticles(&model, Ar, DLC, &disp);	// 粒子の描画
	
	glPopMatrix();
	//-----------------------------------------------------------

	
	// ステップ数などの描画--------------------------------------
	glViewport(0, height - 80, 200, 80);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 2.5, 0.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_LIGHTING);
	glPushMatrix();
	RenderText(&disp, &model);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	//-----------------------------------------------------------

	// 操作盤の描画----------------------------------------------
	glViewport(width - 280, 0, 280, 101);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 280, 0.0, 101, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_LIGHTING);
	glPushMatrix();
	RenderMenu(&model, &disp);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	//-----------------------------------------------------------
	
	glutSwapBuffers();
};

void Mouse(int button, int state, int x, int y){
	int width, height;

	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);

	switch (state){
	case GLUT_DOWN:
		if (width - 150 < x && x < width - 80 && height - 140<y && y<height - 20){
			if (disp.moviespeed < 0) disp.moviespeed = 0;
			disp.moviespeed++;
		}
		else if (width - 210 <x && x<width - 150 && height - 60<y && y<height - 20){
			disp.moviespeed = 0;
		}
		else if (width - 280<x && x< width - 210 && height - 60<y && y<height - 20){
			if (disp.moviespeed > 0) disp.moviespeed = 0;
			disp.moviespeed--;
		}
		else if (width - 280<x && x< width - 260 && height - 20<y && y<height){
			disp.curstep -= model.output_gap;
		}
		else if (width - 100<x && x<width - 80 && height - 20<y && y<height){
			disp.curstep += model.output_gap;
		}
		else if (width - 260<x && x<width - 100 && height - 20<y && y<height){
			disp.curstep = model.output_gap*((x - width + 255) * (model.CVS_step_num + model.Sp_step_num) / (150 * model.output_gap));
			if (disp.curstep > model.CVS_step_num + model.Sp_step_num) disp.curstep = model.CVS_step_num + model.Sp_step_num;
			else if (disp.curstep<0) disp.curstep = 0;
			mous.mode = 2;
		}
		else if (width - 80<x && x<width && height - 80<y && y<height - 60){
			disp.view_mode += 1;
			disp.view_mode %= 2;
			disp.rend_part = 0;
		}
		else if (width - 80<x && x<width && height - 60<y && y<height - 40 && disp.view_mode == 0){
			disp.rend_part += 1;
			disp.rend_part %= 2;
		}
		else if (width - 80<x && x<width && height - 40<y && y<height - 20){
			disp.depo_mode = 0;
		}
		else if (width - 80<x && x<width && height - 20<y && y<height){
			if (disp.depo_mode == 1) disp.depo_mode = 2;
			else disp.depo_mode = 1;
		}
		else if (width - 80<x && x<width && height - 100<y && y<height - 80){
			disp.Render++;
			disp.Render %= 2;
		}
		else mous.mode = 1;
		break;
	case GLUT_UP:
		mous.mode = 0;
		break;
	}
	mous.button = button;
	mous.xstart = x;
	mous.ystart = y;
};

void Motion(int x, int y){
	int movx, movy;
	int width;
	movx = x - mous.xstart;
	movy = y - mous.ystart;

	width = glutGet(GLUT_WINDOW_WIDTH);

	switch (mous.mode){
	case 1:
		switch (mous.button){
		case GLUT_LEFT_BUTTON:
			disp.viewpos[3] -= movx;
			disp.viewpos[2] -= movy;
			break;
		case GLUT_RIGHT_BUTTON:
			disp.viewpos[0] -= (float)movy;
			break;
		}
		break;

	case 2:
		if (width - 260<x && x<width - 100) disp.curstep += (int)((double)movx * ((double)(model.CVS_step_num + model.Sp_step_num) / 150));
		break;
	}
	mous.xstart = x;
	mous.ystart = y;
	glutPostRedisplay();
}

/*
*	Initialize Open GL functions.
*/
int InitializeGL(int argc, char **argv){
	// Create Window.
	glutInit(&argc, argv);
	glutInitWindowSize(560, 560);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutCreateWindow(NAME);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Set events.
	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutIdleFunc(Idle);

	//Set lights.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_AUTO_NORMAL);

	glEnable(GL_MAP2_VERTEX_3);

	return 0;
}

int main(int argc, char**argv){
	//Load data and Initialize.
	loaddata(&model);
	loadfile(&deta);
	InitDispParam(&model, &disp);
	InitializeGL(argc, argv);

	glutMainLoop();
	free(mesh);


	return 0;
}
