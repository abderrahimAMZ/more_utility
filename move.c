

/*
*
* initialy, we will build just a utility that reads a file and push it to the standard
* out put stream
*
*/






#include <stdio.h>
#include <stdlib.h>
#define LINELENGTH 512

int read_file_to_stdout(char * file_location){
	// open the file
	FILE * file = fopen(file_location,"r");
	// check if the file is opened
	if (file == NULL){
		fprintf(stderr,"Error: file not found\n");
		exit(0);
	}
	// allocate memory for the buffer
	char buffer[LINELENGTH];
	// print the file
	while (fgets(buffer,LINELENGTH,file) != NULL){
		fputs(buffer,stdout);
	}
	// close the file
	fclose(file);
	return EXIT_SUCCESS;
}


int main(int argc, char *argv[])
{
	if ( argc == 1){
		fprintf(stderr,"target file not provided\n");
		exit(0);
	}
	char * file_location = (char*)argv[1];
	int result = read_file_to_stdout(file_location);

	return result;
}
