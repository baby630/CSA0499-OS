#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_FILENAME_LEN 50
#define MAX_FOLDER_NAME_LEN 20
#define MAX_SUBFOLDERS 10
#define MAX_FILES 20

struct folder {
    char folderName[MAX_FOLDER_NAME_LEN];
    int numFiles;
    char files[MAX_FILES][MAX_FILENAME_LEN];
};

struct directory {
    struct folder folders[MAX_SUBFOLDERS];
    int numFolders;
};

int createFolder(char *folderName) {
    struct stat st = {0};
    if (stat(folderName, &st) == -1) {
        mkdir(folderName, 0700);
        return 1;
    }
    return 0;
}

void addFileToFolder(struct folder *folder, char *fileName) {
    strcpy(folder->files[folder->numFiles], fileName);
    folder->numFiles++;
}

void organizeFiles(struct directory *dir) {
    for (int i = 0; i < dir->numFolders; i++) {
        createFolder(dir->folders[i].folderName);
        for (int j = 0; j < dir->folders[i].numFiles; j++) {
            char src[MAX_FILENAME_LEN + MAX_FOLDER_NAME_LEN];
            sprintf(src, "%s/%s", dir->folders[i].folderName, dir->folders[i].files[j]);
            rename(dir->folders[i].files[j], src);
        }
    }
}

int main() {
    struct directory dir;
    dir.numFolders = 0;

    strcpy(dir.folders[dir.numFolders].folderName, "subfolder1");
    dir.folders[dir.numFolders].numFiles = 0;
    addFileToFolder(&dir.folders[dir.numFolders], "file1.txt");
    addFileToFolder(&dir.folders[dir.numFolders], "file2.txt");
    addFileToFolder(&dir.folders[dir.numFolders], "file3.txt");
    dir.numFolders++;

    strcpy(dir.folders[dir.numFolders].folderName, "subfolder2");
    dir.folders[dir.numFolders].numFiles = 0;
    addFileToFolder(&dir.folders[dir.numFolders], "file4.txt");
    addFileToFolder(&dir.folders[dir.numFolders], "file5.txt");
    addFileToFolder(&dir.folders[dir.numFolders], "file6.txt");
    dir.numFolders++;

    organizeFiles(&dir);

    printf("Folder structure after organization:\n");
    for (int i = 0; i < dir.numFolders; i++) {
        printf("%s\n", dir.folders[i].folderName);
        for (int j = 0; j < dir.folders[i].numFiles; j++) {
            printf("  - %s\n", dir.folders[i].files[j]);
        }
    }

    return 0;
output:

Folder structure after organization:
subfolder1
  - file1.txt
  - file2.txt
  - file3.txt
subfolder2
  - file4.txt
  - file5.txt
  - file6.txt
