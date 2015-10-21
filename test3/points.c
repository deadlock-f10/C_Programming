#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Max_Points 15
struct point{
	double x;
	double y;
};
typedef struct point* Point;
double triangle(Point A, Point B , Point C);
double polygon(int N,Point *P);
int main()
{
	Point *P;
	P = malloc(sizeof(Point) * 20);
	int i=-1;
	do{
		P[++i] = malloc(sizeof(struct point));
	}while(scanf("%lf %lf",&(P[i]->x),&(P[i]->y)) != EOF);
	printf("%.2f\n",polygon(i,P));
	return 0;
}
double triangle(Point A, Point B , Point C)
{
	return fabs(((A->x)*(B->y - C->y)+(B->x)*(C->y - A->y)+(C->x)*(A->y - B->y))/(double)2);
}
double polygon(int N,Point *P){
	double area = 0;
	int i;
	for(i = 1 ; i < N-1 ; i++){
		area += triangle(P[0],P[i],P[i+1]);
	}
	return area;
}
