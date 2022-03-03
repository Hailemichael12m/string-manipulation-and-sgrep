/*Assignment number 2
Name: Hailemichael Molla Gashaw
Student Id: 20190771*/

#include <stdio.h>
#include <stdlib.h>
//#include <string.h> /* for skeleton code */
#include <unistd.h> /* for getopt */
#include "str.h"


#define MAX_STR_LEN 1023

#define FALSE 0
#define TRUE  1

/*
 * Fill out your own functions here (If you need)
 */
int recur(char *buffer, char *pattern){ // recursive function 
  
  if(!(*pattern)){ //check whether pattern is NULL or not
    return TRUE;
  }

   if (!(StrFindChr(pattern, '*'))){ //check if pattern has * in it
    return FALSE; //if there is no *, get out of the recur function
  }
 
  char *p2;
  while (*pattern == '*'){ //do nothing and go to the next character when it encounters *
    pattern++;
  }

  char ar[MAX_STR_LEN + 1]; //array to store the pattern
  p2 = ar;  //p2 points to the first element of ar
  while(*pattern != '\0'){
    if(*pattern != '*')
      *(p2++) = *(pattern++); //copy the pattern to ar
    else
      break;
  }

  *p2= '\0';

  if (StrFindStr(buffer, ar)){ //Search pattern in buffer line
    buffer = StrFindStr(buffer, ar);
    buffer = buffer + StrGetLength(ar); //buffer points to the string after pattern

    if(recur(buffer, pattern)){ // recursively call the function
      return TRUE;
    }
    else {
      return FALSE;
    }
  }
  return FALSE;

}
/*--------------------------------------------------------------------*/
/* PrintUsage()
   print out the usage of the Simple Grep Program                     */
/*--------------------------------------------------------------------*/
void
PrintUsage(const char* argv0)
{
  const static char *fmt =
	  "Simple Grep (sgrep) Usage:\n"
	  "%s pattern [stdin]\n";

  printf(fmt, argv0);
}
/*-------------------------------------------------------------------*/
/* SearchPattern()
   Your task:
   1. Do argument validation
   - String or file argument length is no more than 1023
   - If you encounter a command-line argument that's too long,
   print out "Error: argument is too long"

   2. Read the each line from standard input (stdin)
   - If you encounter a line larger than 1023 bytes,
   print out "Error: input line is too long"
   - Error message should be printed out to standard error (stderr)

   3. Check & print out the line contains a given string (search-string)

   Tips:
   - fgets() is an useful function to read characters from file. Note
   that the fget() reads until newline or the end-of-file is reached.
   - f//printf(sderr, ...) should be useful for printing out error
   message to standard error

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
SearchPattern(const char *pattern)
{
  char buf[MAX_STR_LEN + 2];
  
  //int chr;
  unsigned long int length;
  /*
   *  TODO: check if pattern is too long
   */
  if ((length = StrGetLength(pattern)) > MAX_STR_LEN){ //check if pattern is too long
    fprintf(stderr, "Error: pattern is too long\n");
    return FALSE;
  }


  /* Read one line at a time from stdin, and process each line */
  while (fgets(buf, sizeof(buf), stdin)) {
    /* TODO: check the length of an input line */
    if((length = StrGetLength(buf)) > MAX_STR_LEN){ //check if input length is too long
      fprintf(stderr, "Error: Input line is too long\n");
      return FALSE;
    }
    /* TODO: fill out this function */
    if (recur(buf, (char *)pattern)){ //call recur function to recursively check all lines when pattern has * in it
      printf("%s", buf);
    }
    else if (StrFindStr(buf, pattern)){ //if pattern has no * in it, just search for the string 
      printf("%s", buf);
      }
    }


  

  return TRUE;
}
/*-------------------------------------------------------------------*/
int
main(const int argc, const char *argv[])
{
  /* Do argument check and parsing */
  if (argc < 2) {
	  fprintf(stderr, "Error: argument parsing error\n");
	  PrintUsage(argv[0]);
	  return (EXIT_FAILURE);
  }

  return SearchPattern(argv[1]) ? EXIT_SUCCESS:EXIT_FAILURE;
}
