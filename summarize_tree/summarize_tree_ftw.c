#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <ftw.h>

#define MAX_FTW_DEPTH 16
int num_dirs;
int num_regs;

static int callback(const char *fpath, const struct stat *sb, int typeflag) {
	// Define stuff here
	// FTW_F is a type flag for regular files
	// FTW_D is a type flag for directories that can be opened 
	if(typeflag == FTW_F){
		num_regs++;
	}
	if(typeflag == FTW_D){
		num_dirs++;
	}
	return 0;
	   }
	    
int main(int argc, char** argv) {
	// Check arguments and set things up
	// following main from sumarize_tree.c
	if(argc != 2){//check for the correct amount of arguements put in
		 printf ("Usage: %s <path>\n", argv[0]);
		 printf ("	 where <path> is the file or root of the tree you want to summarize.\n");
		 return 1;
	}
	//setting global variable to 0
	num_dirs=0;
	num_regs=0;

	ftw(argv[1], callback, MAX_FTW_DEPTH);

	// Print out the results
	printf("There were %d directories.\n",num_dirs);
	printf("There were %d regular files.\n",num_regs);
	return 0;
	}
