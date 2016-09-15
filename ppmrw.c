#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int argCheck(char *argv[], FILE* in);
void buff(FILE* in, char type);
int getSize(FILE* input);
char headCheck(FILE* input);

typedef	struct PixelT {
	int r,g,b;
} PixelT;

typedef	struct PixelS {
	char pixel[9000];
} PixelS;

PixelS binBuff;
PixelT *intBuff;

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

		char type = headCheck(in);
		if (type == 'n') {return(1);}
		
		buff(in, type);
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

void buff(FILE* in, char type) {

	if (type == '6') {

		int ch, count;
		count = 0;
		fread(binBuff.pixel, sizeof(char),getSize(in),in);
	}

	else if (type == '3') {
		
	}

	else {
		fprintf(stderr, "This is not a valid header file\n");
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

char headCheck(FILE* input) {
	char type, plc;
	type = (char) fgetc(input);
	char check[3];
	fgetc(input);
	fgetc(input);
	while(((char)fgetc(input)) != '\n') {}

	for (int i = 0; i < 4;i++) {
		check[i] = (char)fgetc(input);
	}

	if(strcmp(check,"255") < 0) {
		type = 'n';
		fprintf(stderr, "Invalid header file\n");
	}

	return type;
}
