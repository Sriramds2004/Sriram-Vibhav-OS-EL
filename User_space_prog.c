
//This is the program which uses the system call

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MAX_FILE_PATH_LEN 256
#define SHA256_DIGEST_SIZE 32

int main() {
    const char *filename = "/path/to/your/file.txt";  // Update with the path to your file
    unsigned char hash_output[SHA256_DIGEST_SIZE];
    int ret;

    // Call the syscall
    ret = syscall(__NR_hash_file, filename, strlen(filename), hash_output);
    if (ret < 0) {
        perror("syscall");
        exit(EXIT_FAILURE);
    }

    // Print the hash output
    printf("SHA-256 hash of %s:\n", filename);
    for (int i = 0; i < SHA256_DIGEST_SIZE; i++) {
        printf("%02x", hash_output[i]);
    }
    printf("\n");

    return 0;
}

