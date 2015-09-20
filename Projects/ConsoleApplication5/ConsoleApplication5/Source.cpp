#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
	double totalscore;
	double maxs = 0;
	int people = 0;
	scanf("%d", &people);
	int i = 0;
	typedef struct {
		int a, b, c, d, e;
		double total;
	} Position;                /* à íuÇï\Ç∑ç\ë¢ëÃ */
	Position score[1000];


	for (i = 0; i < people; i++)
	{
		scanf("%d %d %d %d %d",
			&score[i].a, &score[i].b, &score[i].c, &score[i].d, &score[i].e);
		totalscore = score[i].a + score[i].b + score[i].c + score[i].d + (score[i].e *(110 / 900));
		if (totalscore > maxs)
		{
			maxs = totalscore;
		}

	}
	printf("%f", maxs);
	return 0;
}

