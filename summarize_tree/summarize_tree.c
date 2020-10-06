#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static int num_dirs, num_regular;

bool is_dir(const char* path) {
  /*
   * Use the stat() function (try "man 2 stat") to determine if the file
   * referenced by path is a directory or not.  Call stat, and then use
   * S_ISDIR to see if the file is a directory. Make sure you check the
   * return value from stat in case there is a problem, e.g., maybe the
   * the file doesn't actually exist.
   */
	bool result = false;
	struct stat *buf = malloc(sizeof(struct stat));
	if(stat(path, buf)>0){ 
		free(buf);
		return false;
	}
	result = S_ISDIR(buf -> st_mode);// result will either be set to true or false
	
	free(buf);
	return result;
}

/* 
 * I needed this because the multiple recursion means there's no way to
 * order them so that the definitions all precede the cause.
 */
void process_path(const char*);

void process_directory(const char* path) {
	
	DIR *dir = opendir(path);//open directory
	//check to make sure the directory sent in is not null
	if(dir == NULL){
		return;
	}
	num_dirs++;

	struct dirent *direntThing;
	chdir(path);
	while((direntThing = readdir(dir)) != NULL){
	if( strcmp(direntThing -> d_name,".") != 0 && strcmp(direntThing->d_name,"..") != 0 ){
		process_path(direntThing->d_name);	
		} 
	}
	chdir("..");
	closedir(dir);
}

void process_file(const char* path) {
	num_regular++;
}

void process_path(const char* path) {
  if (is_dir(path)) {
    process_directory(path);
  } else {
    process_file(path);
  }
}

int main (int argc, char *argv[]) {
  // Ensure an argument was provided.
  if (argc != 2) {
    printf ("Usage: %s <path>\n", argv[0]);
    printf ("       where <path> is the file or root of the tree you want to summarize.\n");
    return 1;
  }

  num_dirs = 0;
  num_regular = 0;

  process_path(argv[1]);

  printf("There were %d directories.\n", num_dirs);
  printf("There were %d regular files.\n", num_regular);

  return 0;
}
