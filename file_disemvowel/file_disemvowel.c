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

/*
 * Copy all the non-vowels from in_buf to out_buf.
 * num_chars indicates how many characters are in in_buf,
 * and this function should return the number of non-vowels
 * that were copied over.
 */
int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    int i;
    int num_non_vowels = 0; //Warning: This number also includes all null characters
    for (i=0; i<num_chars; i++) {
	if(is_vowel(in_buf[i]) == false) {
	  out_buf[num_non_vowels] = in_buf[i];
	  num_non_vowels++;
	}
    }

    return num_non_vowels;
}

/*
 * Copy all the non-vowels from inputFile to outputFile.
 * Create input and output buffers, and use fread() to repeatedly read
 * in a buffer of data, copy the non-vowels to the output buffer, and
 * use fwrite to write that out.
 */
void disemvowel(FILE* inputFile, FILE* outputFile) {
    char *in_buf;
    char *out_buf;
    char *final_output;
    int out_length;
    in_buf = (char*) calloc(BUF_SIZE, sizeof(char));
    out_buf = (char*) calloc(BUF_SIZE, sizeof(char));

    fread(in_buf, sizeof(char), BUF_SIZE, inputFile);
    copy_non_vowels(BUF_SIZE, in_buf, out_buf);
    out_length = strlen(out_buf);

    final_output = (char*) calloc(out_length, sizeof(char));
    for (int i = 0; i<out_length; i++) {
	final_output[i] = out_buf[i];
    }

    fwrite(final_output, sizeof(char), out_length, outputFile);

    free(in_buf);
    free(out_buf);
    free(final_output);
}

int main(int argc, char *argv[]) {
    FILE *inputFile;
    FILE *outputFile;

    //Code that processes the command line arguments
    //and sets up inputFile and outputFile.
    switch (argc) {
      case 1:
	inputFile = stdin;
	outputFile = stdout;
        disemvowel(inputFile, outputFile);
	break;
      case 2:
	inputFile = fopen(argv[1], "r");
	outputFile = stdout;
        disemvowel(inputFile, outputFile);
	fclose(inputFile);
	break;
      case 3:
	inputFile = fopen(argv[1], "r");
	outputFile = fopen(argv[2], "a");
	disemvowel(inputFile, outputFile);
	fclose(inputFile);
	fclose(outputFile);
	break;
      default:
	printf("ERROR: Incorrect syntax. Please put the input file first, followed by the output file.\n");
	break;
    }
    return 0;
}
