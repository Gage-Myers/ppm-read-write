#include <stdio.h>
#include <stdlib.h>

int argCheck(char *argv[], FILE* in);
void buff(FILE* in);
int getSize(FILE* input);

typedef	struct Pixel {
	unsigned char pixVal;
} Pixel;

Pixel *imgBuff;

int main(int argc, char *argv[]) {

	// Begin by ensuring all arguments have been entered
	// to execute the code
	
	if (argc != 4) {
		printf("Insufficient number of arguments\n");
		return(1);
	} else{

		// Opens the given ppm file from argv
		// then calls a funcion that will check each
		// argument and ensure they are formatted correctly
		
		FILE* in = fopen(argv[2], "r");
		if (argCheck(argv, in)) {return(1);}
		
		buff(in);
		fclose(in);

		printf("Testing...\n");
		return 0;
	}
}

/* This function checks the arguments given
 * in the command line to ensure they are
 * compatible with the program */

int argCheck(char *argv[], FILE* in) {

	// The first check is to ensure that ppm 3 or 6 is selected

	if (!(atoi(argv[1]) == 3 || atoi(argv[1]) == 6)) {
		printf("First argument must be 3 or 6\n");
		return 1;
	}

	// The second check is ensuring the input and
	// output files are .ppm

	int c = fgetc(in);
	if (c != 'P') {
		fprintf(stderr, "Error, this is not a ppm file.\n");
		return 1;
	}
	
	return 0;
}

/* This function is used to read from the input
 * ppm file and stores it into a buffer file 
 * that will later be used to convert into the output
 * file */

void buff(FILE* in) {
	int ch, count;
	count = 0;

	imgBuff = malloc(sizeof(Pixel) * getSize(in));

	while ((ch = fgetc(in))!= EOF) {
		imgBuff[count].pixVal = (char) ch;
		count++;
	}
}

int getSize(FILE* input) {
	if(input == NULL) return -1;

    long pos = ftell(input);

	if(fseek(input, 0, SEEK_END) == -1) return -1;
	
	long size = ftell(input);
	
	if(size == -1) return -1;
	
	if(fseek(input, pos, SEEK_SET) == -1) return -1;

	return size;
}
