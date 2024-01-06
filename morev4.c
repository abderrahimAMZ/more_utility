/*
*
*
* in this version : i added reverse video feature
*/

#include <stdio.h>
#include <stdlib.h>

#define	PAGELEN	20
#define	LINELEN	512

void do_more(FILE *);
int  get_input(FILE*);
int main(int argc , char *argv[])
{
   int i=0;
   if (argc == 1){
      do_more(stdin);
   }
   FILE * fp;
   while(++i < argc){
      fp = fopen(argv[i] , "r");
      if (fp == NULL){
         perror("Can't open file");
         exit (1);
      }
      do_more(fp);
      fclose(fp);
   }  
   return 0;
}

void do_more(FILE *fp)
{
   int num_of_lines = 0;
   int rv;
   char buffer[LINELEN];

   while (fgets(buffer, LINELEN, fp)){

      // wee nned to check if is_more is set, we need to set the cursor one line above, else nothing to be changed.
      fputs(buffer, stdout);
      num_of_lines++;
      if (num_of_lines == PAGELEN){
         fprintf(stdout,"\033[7m --more--(?%)\033[m");
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
