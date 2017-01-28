#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>

int main() {

    char *dir = ".";
    struct dirent *store;
    DIR *d = opendir(dir);

    int size;
    store = readdir(d);
    char directories[1000] = "Directories:\n\t";
    char regfiles[1000] = "Regular files:\n\t";
    while(store) {
        if(store->d_type == DT_DIR) {
            strcat(directories, store->d_name);
            strcat(directories, "\n\t");
        }
        if(store->d_type == DT_REG) {
            struct stat st;
            stat(store->d_name, &st);
            size += (int)(st.st_size);
            strcat(regfiles, store->d_name);
            strcat(regfiles, "\n\t");
        }
        store = readdir(d);
    }
    closedir(d);

    directories[strlen(directories)-1] = 0;
    regfiles[strlen(regfiles)-1] = 0;
    printf("Statistics for directory: %s\n", dir);
    printf("Total Directory Size: %d\n", size);
    printf("%s", directories);
    printf("%s", regfiles);

    return 0;
 }
