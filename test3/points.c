#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Max_Points 15
struct point{
	float x;
	float y;
};
typedef struct point* Point;
float triangle(Point A, Point B , Point C);
float polygon(int N,Point *P);
int main()
{
	Point *P;
	int N;
	scanf("%d",&N);
	P = malloc(sizeof(Point) * N);
	int i;
	for(i = 0 ; i < N ; i++){
		P[i] = malloc(sizeof(struct point));
		scanf("%f %f",&(P[i]->x),&(P[i]->y));
	}
	printf("%.2f\n",polygon(N,P));
	return 0;
}
float triangle(Point A, Point B , Point C)
{
	return fabs(((A->x)*(B->y - C->y)+(B->x)*(C->y - A->y)+(C->x)*(A->y - B->y))/(float)2);
}
float polygon(int N,Point *P){
	float area = 0;
	int i;
	for(i = 1 ; i < N-1 ; i++){
		area += triangle(P[0],P[i],P[i+1]);
	}
	return area;
}
