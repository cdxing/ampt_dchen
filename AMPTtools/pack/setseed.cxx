#include <iostream>
#include <fstream>
#include "TRandom.h"
#include "stdio.h"
#include <sstream>
#include <string>

using namespace std;


void setseed(int seed0) {

	gRandom->SetSeed(seed0);

	int seed1 = int(gRandom->Uniform(0,1)*100000000);
	int seed2 = int(gRandom->Uniform(0,1)*1000000);

	FILE* input = fopen("input.ampt","r+");

	char newseed1[16];
	char newseed2[16];

	sprintf(newseed1,"%d",seed1);//convert int seed into char
	sprintf(newseed2,"%d",seed2);

	for(int i=0;i<28;i++) {
		fscanf(input,"%*[^\n]%*c");//move the file pointer to the 29th line
	}

	fputs(newseed1,input);
	fscanf(input,"%*[^\n]%*c");
	fputs(newseed2,input);

	fclose(input);
}


int main(int argc, char **argv) {

	int seed0 = 0;
	int iJob = 0;
	int iSim = 0;


	if(argc==1) {
		seed0 = 0;
	} else if(argc==2) {
		iJob = atoi(argv[1]);
		seed0 = iJob;
	} else if(argc==2) {
		iJob = atoi(argv[1]);
		iSim = atoi(argv[2]);
		seed0 = iJob*100+iSim;
	} else {
		seed0 = 0;
	}

	setseed(seed0);

	return 0;
}
