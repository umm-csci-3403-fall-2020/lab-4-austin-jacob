#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "disemvowel.h"

  //Checks to see if the given char is a vowel and returns
  //a 0 if it is, and a 1 if it is not.
int notAVowel(char str) {
  switch (str) {
    case 'a':
    case 'A':
    case 'e':
    case 'E':
    case 'i':
    case 'I':
    case 'o':
    case 'O':
    case 'u':
    case 'U':
      return 0;
      break;
    default:
      return 1;
      break;
  }
}

char *disemvowel(char *str) {
  int length;
  int i;
  int newLength = 0;
  int location = 0;
  length = strlen(str);
  char *result;

  //Checks to see if the string contains anything.
  //If it doesn't contain anything, return the string.
  if (length <= 0) {
    return str;
  }

  //Count the number of vowels in str
  for (i=0; i<length; i++) {
    if (notAVowel(str[i]) == 1) {
    newLength++;
    }
  }

  //The actual disemvowel process. First, it creates
  //a new array called result that is based off of
  //newLength. It will then loop through the given string,
  //see if that character is a vowel, and add it to
  //result if it's not a vowel.
  result = (char*) calloc(newLength+1, sizeof(char));

  for (i=0; i<length; i++) {
    if (notAVowel(str[i])==1) {
      result[location] = str[i];
      location++;
    }
  }

  return result;
}

