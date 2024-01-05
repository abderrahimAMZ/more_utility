

/*
*
* initialy, we will build just a utility that reads a file and push it to the standard
* out put stream
*
*/




#include <stdio.h>
#include <stdlib.h>


int read_file_to_stdout(char * file_location){
	// open the file
	FILE * file = fopen(file_location,"r");
	// check if the file is opened
	if (file == NULL){
		fprintf(stderr,"Error: %s not found\n",file_location);
		return -1;
	}
	
	// allocate memory for the buffer
	char * buffer = malloc(sizeof(char)*1024);
	// print the file
	while (fgets(buffer,1024,file) != NULL){
		printf("%s",buffer);
	}
	// close the file
	fclose(file);
	return 0;
}


int main(int argc, char *argv[])
{
	// i need help here, give me the solution to reading from a file
	
	if ( argc > 1){
		int current_arg = 1;
		while(current_arg < argc) {
			char * file_location = (char*)argv[current_arg];
			read_file_to_stdout(file_location);
			current_arg++;
			// display a seperator
			if (current_arg < argc){
				printf("\n");
				printf("--------------------------------------------------\n");
				printf(file_location,stdout);
				printf("\n");
				printf("--------------------------------------------------\n");
				printf("\n");

			}

		}
		

	}
	else {
		exit(-1);
	}

	return EXIT_SUCCESS;
}


