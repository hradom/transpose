//Hannah Radom
//I pledge my honor that I have abided by the Stevens Honor System

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char* argv[]){
	//set up input array
	//blockwid is a power of 2
	if(argc != 4){
		perror("Usage: transpif <height> <width> <blockwidth>");
		exit(1);
	}

	int height = atoi(argv[1]);
	int width = atoi(argv[2]);
	int blockwid = atoi(argv[3]);
	struct timeval tvb, tva;

	float * ina;
	ina = (float *) malloc(width * height * sizeof(float));
	if(ina == NULL){
		perror("Malloc failed\n");
		exit(1);
	}
	for(int i = 0; i < (width*height); i++){
		//initialize input array with random floats
		ina[i] = 200 * ((float)rand()/(float)RAND_MAX) -100;
	}

	//set up empty output array
	float * oa;
	oa = (float *) malloc(width * height * sizeof(float));
	if(oa == NULL){
		perror("Malloc failed\n");
		exit(1);
	}

	//transpose in blocks of width blockwid, with an if condition to check
	//that only legal memory address are accessed
	//by making sure j is < height, and i < width
	int i, j, k, l, m = 0;
	double t1, t2;

	//make array for 100 timing results
	float * ta;
	ta = (float * ) malloc(100 * sizeof(float));
	if(ta == NULL){
		perror("Malloc failed\n");
		exit(1);
	}

	for(m = 0; m < 100; m++){
		//take before transpose time
		gettimeofday(&tvb, NULL);
		//transpose array
		for(l = 0; l < height; l += blockwid){
			for(k = 0; k < width; k += blockwid){
				for(j = l; j < (l + blockwid); j++){
					for(i = k; i < (k + blockwid); i++){
						if((j < height) && (i < width)){
							oa[j + (i * height)] = ina[i + (j * width)];
						}
					}
				}
			}
		}

		//take after transpose time
		gettimeofday(&tva, NULL);
		t1 = (double) tvb.tv_sec + ((double) tvb.tv_usec / 1000000);
		t2 =  (double) tva.tv_sec + ((double) tva.tv_usec / 1000000);

		//put t2-t1 in memory
		ta[m] = (t2 - t1);
	}

	double sum = 0;
	//sum timing array
	for(m = 0; m < 100; m++){
		sum += ta[m];
	}

	sum = (sum / 100);
	//print transpose time
	printf("time to transpose: %lf\n", sum);

	//free malloc'd memory
	free(ina);
	free(oa);
	free(ta);
	exit(0);
}