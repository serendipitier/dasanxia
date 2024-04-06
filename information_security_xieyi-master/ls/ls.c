#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

void myls(char []);

int main(int ac,char * av[]){
    if (ac == 1) {
        myls(".");
    } else {
        while (--ac) {
            ++av;
            myls(*av);
        }
    }
    return 0;
}
void myls(char dirname[]){
    DIR *dir_ptr;
    struct dirent  *direntp;
    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls1 cannot open %s\n",dirname);
    } else {
        while ((direntp = readdir(dir_ptr)) != NULL)
            printf("%s   ", direntp->d_name);
        printf("\n");
        closedir(dir_ptr);
    }
}
