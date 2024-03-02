#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILE_NAME 100

struct File {
    char name[MAX_FILE_NAME];
    char content[1024];
};

struct Directory {
    char name[MAX_FILE_NAME];
    struct File files[MAX_FILES];
    int num_files;
};

void add_file(struct Directory* dir, const char* file_name, const char* content) {
    if (dir->num_files < MAX_FILES) {
        strcpy(dir->files[dir->num_files].name, file_name);
        strcpy(dir->files[dir->num_files].content, content);
        dir->num_files++;
        printf("File added successfully!\n");
    } else {
        printf("Maximum number of files reached!\n");
    }
}

void display_files(struct Directory* dir) {
    printf("Files in directory %s:\n", dir->name);
    for (int i = 0; i < dir->num_files; i++) {
        printf("%s\n", dir->files[i].name);
    }
}

int main() {
    struct Directory dir;
    strcpy(dir.name, "MyDirectory");
    dir.num_files = 0;

    int choice;
    char file_name[MAX_FILE_NAME];
    char content[1024];

    while (1) {
        printf("\n1. Add file\n");
        printf("2. Display files\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", file_name);
                printf("Enter content: ");
                scanf("%s", content);
                add_file(&dir, file_name, content);
                break;
            case 2:
                display_files(&dir);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}

OUTPUT:

1. Add file
2. Display files
3. Exit
Enter choice: 1
Enter file name: file1.txt
Enter content: This is file 1 content.
File added successfully!

1. Add file
2. Display files
3. Exit
Enter choice: 1
Enter file name: file2.txt
Enter content: This is file 2 content.
File added successfully!

1. Add file
2. Display files
3. Exit
Enter choice: 2
Files in directory MyDirectory:
file1.txt
file2.txt

1. Add file
2. Display files
3. Exit
Enter choice: 3
