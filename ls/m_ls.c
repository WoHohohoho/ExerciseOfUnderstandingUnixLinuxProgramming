#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <time.h>
#include <stdlib.h>

void do_ls(char *dirname);
void do_stat(char *path);
void show_info(char *file_path, struct stat file_info);
void mode_to_letters(int mode, char *result);
char* uid_to_uname(uid_t uid);
char* gid_to_gname(gid_t gid);

int main(int ac, char *args[]){
    if (ac == 1)
        do_ls(".");
    else if (ac > 1)
        while (--ac){
            printf("%s:\n", *(++args));
            do_ls(*args);
        }

    return 0;
}

void do_ls(char *dirname){
    DIR *dir = opendir(dirname);
    struct dirent *ent;

    if (dir == NULL){
        fprintf(stderr, "ls: Can not open %s: ", dirname);
        perror("");
        exit(1);
    }

    while ((ent = readdir(dir)) != NULL){
        char path[128] = "";
        sprintf(path, "%s/%s", dirname, ent->d_name);
        do_stat(path);
    }

    closedir(dir);
}

void do_stat(char *path){
    struct stat file_info;

    if (stat(path, &file_info) == -1){
        perror(path);
    }
    else {
        show_info(path, file_info);
    }
}


void show_info(char *file_path, struct stat file_info){
    char mode[11];

    mode_to_letters(file_info.st_mode, mode);

    printf("%s", mode);
    printf("%4d ", file_info.st_nlink);
    printf("%-8s ", uid_to_uname(file_info.st_uid));    
    printf("%-8s ", gid_to_gname(file_info.st_gid));
    printf("%8ld ", (long)file_info.st_size);
    printf("%.12s ", 4+ctime(&file_info.st_mtimespec.tv_sec));
    printf("%s\n", file_path);
}

void mode_to_letters(int mode, char *result){
    strcpy(result, "----------");

    if (S_ISBLK(mode))  result[0] = 'b';
    if (S_ISREG(mode))  result[0] = 'f';
    if (S_ISDIR(mode))  result[0] = 'd';

    if (mode & S_IRUSR) result[1] = 'r';
    if (mode & S_IWUSR) result[2] = 'w';
    if (mode & S_IXUSR) result[3] = 'x';

    if (mode & S_IRGRP) result[4] = 'r';
    if (mode & S_IWGRP) result[5] = 'w';
    if (mode & S_IXGRP) result[6] = 'x';

    if (mode & S_IROTH) result[7] = 'r';
    if (mode & S_IWOTH) result[8] = 'w';
    if (mode & S_IXOTH) result[9] = 'x';
}

char* uid_to_uname(uid_t uid){
    static char numstr[11];
    struct passwd *pwd_ptr;

    if ((pwd_ptr = getpwuid(uid)) == NULL){
        sprintf(numstr, "%d", uid);
        return numstr;
    }
    else
        return pwd_ptr->pw_name;    
}

char* gid_to_gname(gid_t gid){
    static char numstr[11];
    struct group *grp_ptr;

    if ((grp_ptr = getgrgid(gid)) == NULL){
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else
        return grp_ptr->gr_name;
}
