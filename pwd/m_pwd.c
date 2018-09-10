#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

void print_pwd_path (char *dir);
ino_t get_inode (char *fname);


int main() {
    print_pwd_path(".");
    putchar('\n');
    return 0;
}

void print_pwd_path (char *dir) {
    ino_t inode;
    struct dirent *entry;

    inode = get_inode (".");
    if (inode == get_inode (".."))
        return;

    chdir ("..");
    DIR *dirp;
    dirp = opendir (".");
    while ((entry = readdir (dirp)) != NULL){
        if (entry->d_ino == inode)
            break;
    }

    print_pwd_path (".");
    fprintf(stdout, "/%s", entry->d_name);
    closedir (dirp);
}

ino_t get_inode (char *fname) {
    struct stat info;

    if (stat (fname, &info) == -1) {
        fprintf (stderr, "Can't stat ");
        perror (fname);
        exit (1);
    }

    return info.st_ino;
}
