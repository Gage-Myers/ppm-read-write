#include <stdio.h>
#include <stdlib.h>

int argCheck(char *argv[], FILE* in);
void readP3(FILE* in);
void readP6(FILE* in);

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

		// Opens the ppm file and then check the header
		// to decide which function to call

		int check = fgetc(in);

		if (check == '3') {readP3(in);}

		if (check == '3') {readP6(in);}

		fclose(in);
		printf("Testing...\n");
		return 0;
	}
}

int argCheck(char *argv[], FILE* in) {

	// The first check is to ensure that ppm 3 or 6 is selected

	if (!(atoi(argv[1]) == 3 || atoi(argv[1]) == 6)) {
		printf("First argument must be 3 or 6\n");
		printf("%d\n", atoi(argv[1]));
		return 1;
	}

	// The second check is ensuring the input and
	// output files are .ppm

	int c = fgetc(in);
	if (c != 'P') {
		fprintf(stderr, "Error, this is not a ppm file.\n");
		printf("%d %d %d\n", c, 'p', 'P');
		return 1;
	}
	
	return 0;
}

void readP3(FILE* in) {
	FILE* buff = fopen("buffer.ppm", "w");
	fclose(buff);
}

void readP6(FILE* in) {
	FILE* buff  = fopen("buffer.ppm", "w");
	fclose(buff);
}
