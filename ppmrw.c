#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int argCheck(char *argv[], FILE* in);
void buff(FILE* in, char type);
void write(FILE* out, char outType, int inType);
int getSize(FILE* input);
char headCheck(FILE* input);

typedef	struct Pixel {
	unsigned char data[9000];
} Pixel;

Pixel pixBuff;

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

		FILE* out;

		if (atoi(argv[1]) == 6) {
			out = fopen(argv[3], "wb");
		} else {
			out = fopen(argv[3], "w");
		}

		write(out, type, atoi(argv[1]));
		fclose(out);

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

	int size = getSize(in);

	if (type == '6') {
		fread(pixBuff.data, sizeof(char),getSize(in),in);
	}

	else if (type == '3') {
		int i;
		for (i = 0; i < size; i++) {
			pixBuff.data[i] = fgetc(in);
		}
	}

	else {
		fprintf(stderr, "This is not a valid header file\n");
	}
	
}

/* This function is a helper function
 * that is used to read in the size
 * of the file */

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
	while(((char)fgetc(input)) == '#') {
		while(((char)fgetc(input)) != '\n') {}
	}
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

void write(FILE* out, char outType, int inType) {

	if (outType == '6') {
		if (inType == 6) {
		} else {
		}
	} else {
	}
	
}
