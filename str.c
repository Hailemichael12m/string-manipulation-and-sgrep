/*Assignment number 2
Name: Hailemichael Molla Gashaw
Student Id: 20190771*/


#include <assert.h> /* to use assert() */
#include <stdio.h>
#include <stdlib.h> /* for strtol() */
#include "str.h"
#include <ctype.h>
//#include <limits.h>

/* Your task is: 
   1. Rewrite the body of "Part 1" functions - remove the current
      body that simply calls the corresponding C standard library
      function.
   2. Write appropriate comment per each function
*/

/* Part 1 */
/*------------------------------------------------------------------------*/
size_t StrGetLength(const char* pcSrc)
{
  const char *pcEnd;
  assert(pcSrc); /* NULL address, 0, and FALSE are identical. */
  pcEnd = pcSrc;
	
  while (*pcEnd) /* null character and FALSE are identical. */
    pcEnd++;

  return (size_t)(pcEnd - pcSrc);
}

/*------------------------------------------------------------------------*/
char *StrCopy(char *pcDest, const char* pcSrc)
{
  /* TODO: fill this function */
  assert(pcDest);
  assert(pcSrc);
  char *move = pcDest; //declaring a moving pointer
  while(*pcSrc != '\0'){ 
    *move = *pcSrc;
    move++;
    pcSrc++;
  }
  *move = '\0';  //adding the last null character
  
  return pcDest;
}

/*------------------------------------------------------------------------*/
int StrCompare(const char* pcS1, const char* pcS2)
{
  /* TODO: fill this function */
  assert (pcS1);
  assert (pcS2);
  
  while(*pcS1 == *pcS2) {
    if (*pcS1 == '\0' || *pcS2 == '\0') {  //if this happens, we are done comparing
      break;
   }
    pcS1++;
    pcS2++;
  }
  char d =   *(unsigned char*) pcS1-  *(unsigned char*) pcS2; // difference of the pointers
  if (d < 0){
    return -10;   //PcS1 has less less characters than PcS2...unequal
  }
  else if(d == 0){ //bingo...they are equal
    return 0;
  }
  else if (d > 0) {  //PcS1 has more characters than PcS2...unequal
    return 10;
  }
  return 0;
}
/*------------------------------------------------------------------------*/
char *StrFindChr(const char* pcHaystack, int c)
{
  /* TODO: fill this function */ 
  assert(pcHaystack);
  char *address = (char *) pcHaystack; //address is the moving pointer initiallized at the beggining of pcHaystack
  
  while (*address) {  //move until the last null pointer
    if (*address == c) {
      return address++;
    }
    else {
      address++;
    }
  }
  if (c == '\0'){   //if the int c is the last null character, move the pointer one more step
    return address++;
    
  }
  return 0;
}
/*------------------------------------------------------------------------*/
char *StrFindStr(const char* pcHaystack, const char *pcNeedle)
{
  /* TODO: fill this function */
  assert(pcHaystack);
  assert(pcNeedle);
  int a = 0;//dummy indicator variable
  char *h;
  char *n; 
  char *ch = (char *) pcHaystack;  //declaring a modifyable pointer from const pcHaystack
 
  if (!(*pcNeedle)){
    return ch;
  }
  while (*ch && *ch != '\0'){   
    if (*ch == *pcNeedle){ //we got the starting string similar here...let's go check the rest
      h = ch;              
      n = (char *) pcNeedle;
    
      while (*n){ //to check up to the end of the needle
        if (*h == *n){ //we are getting similar characters
          h++;
          n++;
          a = 0;
        }
        else{  // not all characters of the needle are found
          a = 1; // a changes to 1 to indicate "mission failure"...we could not find all needle characters
          break;
        }

      }
      if (a==0){ //all characters of the needle are found
        return ch;//the address where we first encountered the needle's first character
      }
      else { //if not, contniue checking the remaining Haystack
        ch++;
      }
    }
    else{
      ch++;
    }

  }

  return 0;
} 
/*------------------------------------------------------------------------*/
char *StrConcat(char *pcDest, const char* pcSrc)
{
  /* TODO: fill this function */
  assert(pcDest);
  assert(pcSrc);

  char *move = pcDest; //declaring a moving pointer to apply the same logic as StrCopy
  while(*move){ //going to the last character
    move++;
  }
  while(*pcSrc){ //copy the source string to the destination
    *move = *pcSrc;
    move++;
    pcSrc++;

  }
  *move = '\0';  //add the last null character
  return pcDest;
  
}

/*------------------------------------------------------------------------*/
long int StrToLong(const char *nptr, char **endptr, int base)
{
  /* handle only when base is 10 */
  if (base != 10) return 0;
  assert(nptr);
  unsigned long long int x = 0;
  int negative = 0;   // dummy variable to indicate if a number is negative
  int temp;
  char *digit = (char *) nptr;
  while (!(isdigit(*digit))){     //if digit doesn't come at the beginnig of nptr, check for signs and space
    if (*digit == '+' || *digit == '-'){
      if (*digit == '-'){
        negative = 1; //remember the return value that the number is negative
      }
      digit++;
     
    }
    else if(isspace(*digit)){ 
      while(isspace(*digit)){ //skip the spaces until we encounter digit or alphabet
        digit++;
      }
    }
    else{
      break;
    }
  }
  while (*digit && isdigit(*digit)) { //number conversion to base to long int...from the assignment documentation
    temp = *digit - '0';
    x = 10 * x + temp;
    digit++;
  }
  if(endptr){   //if not NULL pointer, assign the address of the first non-digit character
    *endptr = digit;
  }

  if (negative == 1){ //the number is negative
    if (x == LONG_MAX){ //corner case as the negative of LLONG_MAX is in the long long int range...no underflow 
      return -1*LONG_MAX;
    }
  }
  if (x >= LONG_MAX){ //overflow
    x = LONG_MAX; 
    if (negative == 1){ // underflow
      x = LONG_MIN;
      return x;
    }
}
  return (negative == 0) ? x: -1*x;
  

  /* TODO: fill this function */
}
