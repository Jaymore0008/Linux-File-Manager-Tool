#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

using namespace std;

// Function to list files in a directory
void listFiles(const char* path) {
    DIR* dir = opendir(path);
    if (dir == nullptr) {
        perror("Unable to open directory");
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        cout << entry->d_name << endl;
    }

    closedir(dir);
}

// Function to create a file
void createFile(const char* filename) {
    int fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (fd == -1) {
        perror("Error creating file");
        return;
    }
    cout << "File created: " << filename << endl;
    close(fd);
}

// Function to delete a file
void deleteFile(const char* filename) {
    if (unlink(filename) == -1) {
        perror("Error deleting file");
    } else {
        cout << "File deleted: " << filename << endl;
    }
}

// Function to change file permissions
void changePermissions(const char* filename, mode_t mode) {
    if (chmod(filename, mode) == -1) {
        perror("Error changing permissions");
    } else {
        cout << "Permissions changed for: " << filename << endl;
    }
}

int main() {
    int choice;
    char path[256];
    char filename[256];
    mode_t mode;

    while (true) {
        cout << "\nLinux File Manager Tool\n";
        cout << "1. List Files\n";
        cout << "2. Create File\n";
        cout << "3. Delete File\n";
        cout << "4. Change File Permissions\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter directory path: ";
                cin >> path;
                listFiles(path);
                break;
            case 2:
                cout << "Enter filename to create: ";
                cin >> filename;
                createFile(filename);
                break;
            case 3:
                cout << "Enter filename to delete: ";
                cin >> filename;
                deleteFile(filename);
                break;
            case 4:
                cout << "Enter filename to change permissions: ";
                cin >> filename;
                cout << "Enter permissions in octal (e.g., 755): ";
                cin >> oct >> mode;
                changePermissions(filename, mode);
                break;
            case 5:
                exit(0); 
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
