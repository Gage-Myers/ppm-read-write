#include <stdio.h>
#include <stdlib.h>

int argCheck(char *argv[]);

int main(int argc, char *argv[]) {

	// Begin by ensuring all arguments have been entered
	// to execute the code
	
	if (argc != 4) {
		printf("Insufficient number of arguments\n");
		return(1);
	} else{

		// This calls a funcion hat will check each
		// argument and ensure they are formatted correctly
		
		if (argCheck(argv)) {return(1);}

		FILE* in = fopen(argv[2], "r");
		FILE* out = fopen(argv[3], "w");
/*
		while (fgetc(in) != "EOF" ) {
			// TODO: read in line by line
			// buffer in a struct and
			// then use buffer to write to
			// out.ppm
		}
*/
		fclose(in);
		fclose(out);
		printf("Testing...\n");
		return 0;
	}
}

int argCheck(char *argv[]) {

	// The first check is to ensure that ppm 3 or 6 is selected

	if (!(atoi(argv[1]) == 3 || atoi(argv[1]) == 6)) {
		printf("First argument must be 3 or 6\n");
		printf("%d\n", atoi(argv[1]));
		return 1;
	}

	// The second check is ensuring the input and
	// output files are .ppm
	/*
	FILE* in = fopen(argv[2], "r");
	int c = fgetc(in);
	if (c != 'p') {
		fprintf(stderr, "Error, this is not a ppm file.\n");
		return 1;
	}
	*/
	return 0;
}
