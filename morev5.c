/*
*
*
* in this version : i added reverse video feature
*/

#include <stdio.h>
#include <stdlib.h>

#define	LINELEN	512

void do_more(FILE *,int total_lines);
int  get_input(FILE*);
int count_file_lines(char *filelocation);
int main(int argc , char *argv[])
{
   int i=0;
   if (argc == 1){
      do_more(stdin,0);
   }
   FILE * fp;
   while(++i < argc){
      fp = fopen(argv[i] , "r");
      if (fp == NULL){
         perror("Can't open file");
         exit (1);
      }
      
      int total_lines = count_file_lines(argv[i]);
      do_more(fp,total_lines);
      fclose(fp);
   }  
   return 0;
}

int count_file_lines(char* filelocation)
{
   FILE *fp = fopen(filelocation, "r");
   if (fp == NULL){
      perror("Can't open file");
      exit (1);
   }
   int num_of_lines = 0;
   char buffer[LINELEN];
   while (fgets(buffer, LINELEN, fp))
      num_of_lines++;
   fclose(fp);
   return num_of_lines;
}


void do_more(FILE *fp,int total_lines)
{

   // here, we need to get the file length, in order to calcualte the percentage of the remaining content

   int PAGELEN = getenv("LINES") ? atoi(getenv("LINES")) : 24;

   int num_of_lines = 0;
   int current_file_line = 0;
   int rv;
   char buffer[LINELEN];

   while (fgets(buffer, LINELEN, fp)){

      // wee nned to check if is_more is set, we need to set the cursor one line above, else nothing to be changed.
      fputs(buffer, stdout);
      int file_size = ftell(fp);
      num_of_lines++;
      current_file_line++;
      if (num_of_lines == PAGELEN){
         if (total_lines == 0)
            fprintf(stdout,"\033[7m --more--\033[m");
         else
         fprintf(stdout,"\033[7m --more--(%d%)\033[m", (int)(current_file_line*100/total_lines));
         FILE* cmdstream = fopen("/dev/tty", "r");
         rv = get_input(cmdstream);	     
         if (rv == 0){//user pressed q
            printf("\033[1A\033[2k\033[1G");
            break;//
         }
         else if (rv == 1){//user pressed space bar
            num_of_lines -= PAGELEN;
            printf("\033[1A\033[2k\033[1G");
         }
         else if (rv == 2){//user pressed return/enter
            printf("\033[1A\033[2k\033[1G");
	    num_of_lines -= 1; //show one more line
         }
         else if (rv == 3) //invalid character
            break;
      }
  }
}

int get_input(FILE* cmdstream){

   int c;		
   
     c=getc(cmdstream);
      if(c == 'q')
	 return 0;
      if ( c == ' ' )			
	 return 1;
      if ( c == '\n' )	
	 return 2;	
      return 3;
   return 0;
}
