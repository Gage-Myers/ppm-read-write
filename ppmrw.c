#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int argCheck(char *argv[], FILE* in);
void buff(FILE* in, char type);
void write(FILE* out, int outType, int size);
int getSize(FILE* input);
char headCheck(FILE* input);

typedef	struct Pixel {
	unsigned char r,g,b;
} Pixel;

Pixel *pixBuff;
int width,height,color;

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
		int size = getSize(in);
		if (argCheck(argv, in)) {return(1);}

		char type = headCheck(in);
		if (type == 'n') {return(1);}
		
		buff(in, type);
		fclose(in);

		FILE* out = fopen(argv[3], "w");

		write(out, atoi(argv[1]), size);
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
	int count = 0;
	pixBuff = malloc(sizeof(unsigned char) * width * height);

	if (type == '6') {
		for (int i = 0; i < (size/3); i++) {
			fread(&pixBuff[count].r, sizeof(unsigned char),1,in);
			fread(&pixBuff[count].g, sizeof(unsigned char),1,in);
			fread(&pixBuff[count].b, sizeof(unsigned char),1,in);
			count++;
		}
	}

	else if (type == '3') {
		int tr,tg,tb;
		for (int i = 0; i < (width + height); i++) {
			fscanf(in,"%d%d%d", &tr, &tg,&tb);
			pixBuff[width * height].r = (char)tr;
			pixBuff[width * height].g = (char)tg;
			pixBuff[width * height].b = (char)tb;
		}
	}

	else {
		fprintf(stderr, "This is not a valid header file\n");
	}
	
	printf("%d\n", height);
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

	int count = 0;
	char type;
	type = (char) fgetc(input);
	char check;
	fgetc(input);

	while(((char)fgetc(input)) == '#') {
		while(((char)fgetc(input)) != '\n') {}
	}

	fseek(input, -1, SEEK_CUR);

	fscanf(input, "%d%d%d", &width, &height, &color);

	if(color > 255) {
		type = 'n';
		fprintf(stderr, "Invalid header file\n");
	}

	return type;
}

void write(FILE* out, int outType, int size) {

	if (outType == 6) {

		// This statement will print to the out put file
		// in binary as well as add a P6 header file

		fprintf(out, "P6\n%d %d\n255", width, height);

		for (int i = 0; i < size/3; i++) {
			fprintf(out, "%c", pixBuff[i].r);
			fprintf(out, "%c", pixBuff[i].g);
			fprintf(out, "%c", pixBuff[i].b);
		}

	} else {

		// This statement prints to the output file in ascii format
		// and will also begin with a P3 header file

		fprintf(out, "P3\n%d %d\n255\n", width, height);

		int count;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				fprintf(out, "%d %d %d\t", pixBuff[count].r, pixBuff[count].g, pixBuff[count].b);
				count++;
			}
			fprintf(out, "\n");
		}
	}
	
}
