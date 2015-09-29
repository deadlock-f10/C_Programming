all: data points sigma convert 
	true
data: data.c
	gcc -g -Wall data.c -o data
points: points.c
	gcc -g -Wall points.c -o points -lm
sigma: sigma.c
	gcc -g -Wall sigma.c -o sigma
convert: convert.c
	gcc -g -Wall convert.c -o convert
