#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <cstring>

#define BUF_SIZE 2048

    /*
     * Returns true if c is a vowel (upper or lower case), and
     * false otherwise.
     */
bool is_vowel(char c) {
 switch (c) {
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
      return true;
      break;
    default:
      return false;
      break;
  }
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    /*
     * Copy all the non-vowels from in_buf to out_buf.
     * num_chars indicates how many characters are in in_buf,
     * and this function should return the number of non-vowels
     * that were copied over.
     */
    int i;
    int numNonVowels = 0;
    for (i=0; i<num_chars; i++) {
	if(is_vowel(in_buf[i]) == false) {
	  out_buf[numNonVowels] = in_buf[i];
	  numNonVowels++;
	}
    }

    return numNonVowels;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
    /*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out.
     */
    int numNonVowels;
    char *in_buf;
    char *out_buf;
    char *final_output;
    in_buf = (char*) calloc(BUF_SIZE, sizeof(char));
    out_buf = (char*) calloc(BUF_SIZE, sizeof(char));

    fread(in_buf, sizeof(char), BUF_SIZE, inputFile); //might be sizeof(char*)
    numNonVowels = copy_non_vowels(BUF_SIZE, in_buf, out_buf);

    final_output = (char*) calloc(numNonVowels, sizeof(char));
    for (int i = 0; i<numNonVowels; i++) {
	final_output[i] = out_buf[i];
    }
    fwrite(final_output, sizeof(char), numNonVowels, outputFile); //might be sizeof(char*)

    free(in_buf);
    free(out_buf);
    free(final_output);
}

int main(int argc, char *argv[]) {
    // You should set these to `stdin` and `stdout` by default
    // and then set them to user specified files when the user
    // provides files names as command line arguments.
    FILE *inputFile;
    FILE *outputFile;

    // Code that processes the command line arguments
    // and sets up inputFile and outputFile.
    switch (argc) {
      case 1:
	//Take in from stdin and output to stdout
	inputFile = stdin;
	outputFile = stdout;
        disemvowel(inputFile, outputFile);
	break;
      case 2:
        //Take in a file and output stdout
	inputFile = fopen(argv[1], "r");
	outputFile = stdout;
        disemvowel(inputFile, outputFile);
	fclose(inputFile);
	break;
      case 3:
        //Take in a file and output to a file
	inputFile = fopen(argv[1], "r");
	outputFile = fopen(argv[2], "a"); //Use "a" to append to the file
	disemvowel(inputFile, outputFile);
	fclose(inputFile);
	fclose(outputFile);
	break;
      default:
	//Return an error if the argument does not match the above cases
	printf("ERROR: Incorrect syntax. Please put the input file first, followed by the output file.\n");
	break;
    }
    return 0;
}
