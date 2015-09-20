#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

typedef struct{
	float x, y, z, r;
	int b, c;
}Position;

typedef struct
{

	Position pos[3000];
	int step, particle;
	int count;
}Step;




int file_read(char *filename)
{
	FILE *fp;
	Step *step=0;
	
	char    buf[256];
	int i = 0;
	int j = 0;
	int k = 0;
	int count = 0;
	int step_number = 0;
	int particle_number = 0;
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
			sscanf(buf + 6, "%d %d", &step_number, &particle_number);
			
			step = (Step*)malloc(step_number*sizeof(Step));
		//    Step.pos = (Position*)malloc(particle_number*sizeof(Position));
			
			break;

		case '0':
			sscanf(buf, "%f %f %f %f %d %d",
				&step[i].pos[j].x, &step[i].pos[j].y,
				&step[i].pos[j].z, &step[i].pos[j].r,
				&step[i].pos[j].b, &step[i].pos[j].c);
			++j;
			
			break;
		case'e':
			

			//step[k].count = j;
			//k++;
			j = 0;
		//	free(step);
			i++;

			break;

		default:
			break;

		}
	}
	//printf("%d", count);
	fclose(fp);	return 0;

	
	i = 2;
	for (int m = 0; m < 10; m++)
	{
		printf("%f %f %f %f %d %d",
			step[i].pos[m].x, step[i].pos[m].y,
		step[i].pos[m].z, step[i].pos[m].r,
			step[i].pos[m].b, step[i].pos[m].c); 
	}
}

int main()
{
	file_read("output.txt");

	return 0;
}
