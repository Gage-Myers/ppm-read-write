# ppm-read-write
This application allows for a user to use the command line to convert ppm image files from p6 to p3 and visa versa


Usage:
  ./ppmrw 3 input.ppm output.ppm

Users may only use a 3 or 6 as the first argument to describe which format will be placed in output.ppm


The next argument is the input file which must be located in the local directory in which the program is being run
also this file must be ppm format


Lastly the final argument must be a ppm format file which you would like the output to go to


Funcitonality:
By reading through the file which is passed in each pixel is stored in a structure which has been allocated memory
then each pixel is then either printed directly to the output file or is converted from its native format
into the opposite and is then printed on the output file
